----------------------------------- PROCEDIMIENTOS ALMACENADOS PARA LAS ACTIVIDADES -------------------------------------
DELIMITER //
CREATE PROCEDURE CrearActividad(IN pNombre VARCHAR(100))
END//
DELIMITER ;


----------------------------------------------///////////////////////////------------------------------------------------
------------------------------------ PROCEDIMIENTOS ALMACENADOS PARA LOS REGISTROS --------------------------------------
DELIMITER //
CREATE PROCEDURE AgregarRegistro(IN pIdActividad INT, IN pSegundosConsumidos INT UNSIGNED, IN pDescripcion VARCHAR(255))
BEGIN
-- No hay posibilidad de que ninguno de los parámetros sea nulo (ya que en el programa siempre se ingresarán parámetros) por lo que no se hará un control de esto.
-- Tampoco se hará control de si el ID de Actividad existe, ya que en el programa, al entrar en el menú de la actividad, esta existe.
    DECLARE registrosExistentes INT DEFAULT 0;
    SET registrosExistentes = (
        SELECT COUNT(idRegistro) FROM Registros WHERE idActividad = pIdActividad
    );
    INSERT INTO Registros (idRegistro, idActividad, segundosConsumidos, fechaCreacion, descripcion) VALUES (
        registrosExistentes + 1,
        pIdActividad,
        pSegundosConsumidos,
        NOW(),
        pDescripcion
    );
    UPDATE Actividades SET segundosTotales = segundosTotales + pSegundosConsumidos WHERE idActividad = pIdActividad;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE ModificarTiempoConsumido(IN pIdRegistro INT, IN pIdActividad INT, IN pSegundosConsumidos INT UNSIGNED, OUT mensaje VARCHAR(100))
BEGIN
    IF NOT EXISTS (SELECT * FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad) THEN
        SET mensaje = 'ERROR: No existe el registro seleccionado.';
    ELSE
        UPDATE Registros SET segundosConsumidos = pSegundosConsumidos WHERE idRegistro = pIdRegistro;
        SET mensaje = '¡Tiempo del registro modificado con éxito!';
    END IF;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE ModificarFechaCreacion(IN pIdRegistro INT, IN pIdActividad INT, IN pFechaCreacion DATE, OUT mensaje VARCHAR(100))
BEGIN
    IF NOT EXISTS (SELECT * FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad) THEN
        SET mensaje = 'ERROR: No existe el registro seleccionado.';
    ELSE
        IF (SELECT DATE(pFechaCreacion)) IS NOT NULL THEN
            UPDATE Registros SET fechaCreacion = CONCAT(pFechaCreacion, ' ', TIME(fechaCreacion)) WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad;
            SET mensaje = '¡Fecha del registro modificada con éxito!';
        ELSE
            SET mensaje = 'ERROR: Fecha no válida.';
        END IF;
    END IF;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE ModificarHoraCreacion(IN pIdRegistro INT, IN pIdActividad INT, IN pHoraCreacion TIME, OUT mensaje VARCHAR(100))
BEGIN
    IF NOT EXISTS (SELECT * FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad) THEN
        SET mensaje = 'ERROR: No existe el registro seleccionado.';
    ELSE
        IF (SELECT TIME(pHoraCreacion)) IS NOT NULL THEN
            UPDATE Registros SET fechaCreacion = CONCAT(DATE(fechaCreacion), ' ', pHoraCreacion) WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad;
            SET mensaje = '¡Hora del registro modificada con éxito!';
        ELSE
            SET mensaje = 'ERROR: Hora no válida.';
        END IF;
    END IF;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE ModificarDescripcion(IN pIdRegistro INT, IN pIdActividad INT, IN pDescripcion VARCHAR(255), OUT mensaje VARCHAR(100))
BEGIN
    IF NOT EXISTS (SELECT * FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad) THEN
        SET mensaje = 'ERROR: No existe el registro seleccionado.';
    ELSE
        UPDATE Registros SET descripcion = pDescripcion WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad;
        SET mensaje = '¡Descripción modificada con éxito!';
    END IF;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE EliminarRegistro(IN pIdRegistro INT, IN pIdActividad INT, OUT mensaje VARCHAR(100))
BEGIN
    DECLARE idRegistroViejo INT DEFAULT pIdRegistro + 1;
    DECLARE idRegistroNuevo INT DEFAULT pIdRegistro;
    DECLARE cantidadRegistros INT DEFAULT 0;
    IF NOT EXISTS (SELECT * FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad) THEN
        SET mensaje = 'ERROR: No existe el registro seleccionado.';
    ELSE
        UPDATE Actividades SET segundosTotales =
            segundosTotales - (SELECT segundosConsumidos FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad)
        WHERE idActividad = pIdActividad;
        
        DELETE FROM Registros WHERE idRegistro = pIdRegistro AND idActividad = pIdActividad;

        SET cantidadRegistros = (
            SELECT COUNT(idRegistro) FROM Registros WHERE idActividad = pIdActividad
        );
        WHILE idRegistroNuevo <= cantidadRegistros DO
            UPDATE Registros SET idRegistro = idRegistroNuevo WHERE idRegistro = idRegistroViejo AND idActividad = pIdActividad;
            SET idRegistroViejo = idRegistroViejo + 1;
            SET idRegistroNuevo = idRegistroNuevo + 1;
        END WHILE;

        SET mensaje = '¡Registro eliminado con éxito!';
    END IF;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE ListarRegistros(IN pIdActividad INT)
BEGIN
    SELECT
        idRegistro AS ID,
        CONCAT(segundosConsumidos, ' segundos') AS `Tiempo consumido`,
        fechaCreacion AS `Fecha de creación`,
        descripcion AS `Descripción`
    FROM Registros
    WHERE idActividad = pIdActividad;
END//
DELIMITER ;

DROP PROCEDURE IF EXISTS Mostrar;
DELIMITER //
CREATE PROCEDURE Mostrar(IN pIdActividad INT, IN tiempoFiltro INT UNSIGNED)
BEGIN
    DECLARE sumaRegistros INT DEFAULT (
        SELECT SUM(segundosConsumidos) FROM Registros WHERE idActividad = pIdActividad
    );
    DECLARE sumaTemp INT DEFAULT 0;
    DECLARE indiceRegistro INT DEFAULT 1;
    DECLARE indiceConjunto INT DEFAULT 1;
    DECLARE tiempoVacanteConjunto INT UNSIGNED DEFAULT tiempoFiltro;
    
    DECLARE tiempoRestante INT UNSIGNED;
    DECLARE subTiempo INT UNSIGNED;

    DROP TABLE IF EXISTS Temp;
    CREATE TEMPORARY TABLE Temp (
        id                      INT             AUTO_INCREMENT,
        idConjuntoRegistros     INT             NOT NULL,
        idRegistro              INT             NOT NULL,
        idActividad             INT             NOT NULL,
        segundosConsumidos      INT UNSIGNED    NOT NULL DEFAULT 0,
        PRIMARY KEY(id, idConjuntoRegistros, idRegistro, idActividad)
    );

    WHILE sumaRegistros != sumaTemp DO
        SET tiempoRestante = (SELECT segundosConsumidos FROM Registros WHERE idRegistro = indiceRegistro AND idActividad = pIdActividad);

        WHILE tiempoRestante > 0 DO
            IF tiempoRestante <= tiempoFiltro THEN
                IF tiempoRestante <= tiempoVacanteConjunto THEN
                    SET subTiempo = tiempoRestante;
                ELSE
                    SET subTiempo = tiempoVacanteConjunto;
                END IF;
            ELSE
                SET subTiempo = tiempoVacanteConjunto;
            END IF;

            INSERT INTO Temp(idConjuntoRegistros, idRegistro, idActividad, segundosConsumidos) VALUES (indiceConjunto, indiceRegistro, pIdActividad, subTiempo);
-- IF tiempoVacanteConjunto < subTiempo THEN
--     SELECT tiempoRestante, tiempoVacanteConjunto, subTiempo, indiceRegistro;
-- END IF;
            SET tiempoVacanteConjunto = tiempoVacanteConjunto - subTiempo;
            IF tiempoVacanteConjunto = 0 THEN
                SET tiempoVacanteConjunto = tiempoFiltro;
                SET indiceConjunto = indiceConjunto + 1;
            END IF;

            SET tiempoRestante = tiempoRestante - subTiempo;
        END WHILE;

        SET indiceRegistro = indiceRegistro + 1;
        SET sumaRegistros = (
            SELECT SUM(segundosConsumidos) FROM Registros WHERE idActividad = pIdActividad
        );
        SET sumaTemp = (
            SELECT SUM(segundosConsumidos) FROM Temp WHERE idActividad = pIdActividad
        );
    END WHILE;
    
    SELECT
        t.idConjuntoRegistros AS `ID de conjunto`,
        t.idRegistro AS `ID de registro`, 
        t.segundosConsumidos AS `Tiempo que tomó`,
        r.fechaCreacion AS `Tiempo de realización`,
        r.descripcion AS `Descripción`
    FROM Registros r INNER JOIN Temp t ON r.idRegistro = t.idRegistro AND r.idActividad = t.idActividad
    WHERE r.idActividad = pIdActividad;
END//
DELIMITER ;

DELIMITER //
CREATE PROCEDURE Prueba(IN pIdActividad INT, OUT tiempo INT UNSIGNED)
BEGIN
    SET tiempo = (SELECT segundosConsumidos FROM Registros WHERE idActividad = pIdActividad);
END//
DELIMITER ;

SELECT * FROM Registros
GROUP BY SUM(segundosConsumidos)
ORDER BY idRegistro
WHERE SUM(segundosConsumidos) = 7200;
