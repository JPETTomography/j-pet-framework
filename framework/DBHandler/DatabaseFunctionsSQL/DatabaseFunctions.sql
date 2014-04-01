/* 
  All functions functions which have been added to database.
  Last update 29.03.2014
*/

1)
CREATE OR REPLACE FUNCTION photomultiplierInformationFunction()
RETURNS TABLE
(
  runid integer,
  setupid integer,
  hvpmconnid integer,
  isrightside boolean,
  slot_id integer,
  photomid integer
) AS
$BODY$
BEGIN
  FOR runid, setupid, hvpmconnid, isrightside, slot_id, photomid IN
    SELECT 
      "Run".id AS runid, 
      "Setup".id AS setupid, 
      "HVPMConnection".id AS hvpmconnid, 
      "HVPMConnection".isrightside, 
      "HVPMConnection".slot_id AS slot_id, 
      "PhotoMultiplier".id AS photomid 
    FROM "Run" 
      INNER JOIN "Setup" ON "Run".setup_id = "Setup".id 
      INNER JOIN "HVPMConnection" ON "Setup".id = "HVPMConnection".setup_id 
      INNER JOIN "PhotoMultiplier" ON "HVPMConnection".photomultiplier_id = "PhotoMultiplier".id 
    ORDER BY "HVPMConnection".slot_id
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM photomultiplierInformationFunction();

1.1)
CREATE OR REPLACE FUNCTION photomultiplierInformationFunction(IN p_run_id INTEGER)
RETURNS TABLE
(
  runid integer,
  setupid integer,
  hvpmconnid integer,
  isrightside boolean,
  slot_id integer,
  photomid integer
) AS
$BODY$
BEGIN
  FOR runid, setupid, hvpmconnid, isrightside, slot_id, photomid IN
    SELECT 
      "Run".id AS runid, 
      "Setup".id AS setupid, 
      "HVPMConnection".id AS hvpmconnid, 
      "HVPMConnection".isrightside, 
      "HVPMConnection".slot_id AS slot_id, 
      "PhotoMultiplier".id AS photomid 
    FROM "Run" 
      INNER JOIN "Setup" ON "Run".setup_id = "Setup".id 
      INNER JOIN "HVPMConnection" ON "Setup".id = "HVPMConnection".setup_id 
      INNER JOIN "PhotoMultiplier" ON "HVPMConnection".photomultiplier_id = "PhotoMultiplier".id 
    WHERE "Run".id = p_run_id
    ORDER BY "HVPMConnection".slot_id
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM photomultiplierInformationFunction(1);

2)
CREATE OR REPLACE FUNCTION runDataFunction()
RETURNS TABLE
(
  run_id integer,
  runstart timestamp without time zone,
  filepath character varying(255),
  rundescription character varying(255),
  information character varying(255)
) AS
$BODY$
BEGIN
  FOR run_id, runstart, filepath, rundescription, information IN
    SELECT 
      "Run".id AS run_id, 
      "Run".runstart AS runstart, 
      "Run".filepath AS filepath, 
      "Run".rundescription AS rundescription, 
      "Run".informations AS information 
    FROM "Run"
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM runDataFunction();

3)
CREATE OR REPLACE FUNCTION runDataFunction(IN p_run_id INTEGER)
RETURNS TABLE
(
  run_id integer,
  runstart timestamp without time zone,
  filepath character varying(255),
  rundescription character varying(255),
  information character varying(255)
) AS
$BODY$
BEGIN
  FOR run_id, runstart, filepath, rundescription, information IN
    SELECT 
      "Run".id AS run_id, 
      "Run".runstart AS runstart, 
      "Run".filepath AS filepath, 
      "Run".rundescription AS rundescription, 
      "Run".informations AS information 
    FROM "Run"
    WHERE "Run".id = p_run_id
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM runDataFunction(1);

4)
CREATE OR REPLACE FUNCTION sizeOfTableFunction
(
  p_tableName varchar(100)
)
RETURNS integer 
AS $$
DECLARE
  p_tableSize integer;
BEGIN
  execute 'SELECT count(*) from '||quote_ident(p_tableName) into p_tablesize;
  return p_tableSize;
END;
$$ LANGUAGE plpgsql STRICT;

SELECT * FROM sizeOfTableFunction('Run');

5)
CREATE OR REPLACE FUNCTION thresholdFromTRBConfigEntryBasedOnTOMBInputIdFunction(IN p_run_id INTEGER)
RETURNS TABLE
(
  tombinput_id INTEGER,
  trbtombconnection_id INTEGER,
  trboutput_id INTEGER,
  trbinput_id INTEGER,
  kbtrbconnection_id INTEGER,
  trbconfigentry_id INTEGER,
  trbconfigentry_threshold REAL,
  setup_id INTEGER,
  run_id INTEGER
) AS
$BODY$
BEGIN
  FOR tombinput_id, trbtombconnection_id, trboutput_id, trbinput_id, kbtrbconnection_id, trbconfigentry_id, trbconfigentry_threshold, setup_id, run_id IN
    SELECT 
      "TOMBInput".id AS tombinput_id,
      "TRBTOMBConnection".id AS trbtombconnection_id,
      "TRBOutput".id AS trboutput_id,
      "TRBInput".id AS trbinput_id,
      "KBTRBConnection".id AS kbtrbconnection_id,
      "TRBConfigEntry".id AS trbconfigentry_id,
      "TRBConfigEntry".threshold AS trbconfigentry_threshold,
      "Setup".id AS setup_id,
      "Run".id AS run_id      
    FROM "TOMBInput" 
      INNER JOIN "TRBTOMBConnection" ON "TOMBInput".id = "TRBTOMBConnection".tombinput_id 
      INNER JOIN "TRBOutput" ON "TRBTOMBConnection".trboutput_id = "TRBOutput".id
      INNER JOIN "TRBInput" ON "TRBOutput".trbinput_id = "TRBInput".id
      INNER JOIN "KBTRBConnection" ON "TRBInput".id = "KBTRBConnection".trbinput_id
      INNER JOIN "TRBConfigEntry" ON "KBTRBConnection".id = "TRBConfigEntry".id
      INNER JOIN "Setup" ON "TRBTOMBConnection".setup_id = "Setup".id
      INNER JOIN "Run" ON "Setup".id = "Run".id
    AND
      "Run".id = p_run_id
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM thresholdFromTRBConfigEntryBasedOnTOMBInputIdFunction(1);

6)
CREATE OR REPLACE FUNCTION photomultiplierIdBasedOnTOMBInputIdFunction(IN p_run_id INTEGER)
RETURNS TABLE
(
  tombinput_id INTEGER,
  trbtombconnection_id INTEGER,
  trboutput_id INTEGER,
  trbinput_id INTEGER,
  kbtrbconnection_id INTEGER,
  konradboardoutput_id INTEGER,
  konradboardinput_id INTEGER,
  pmkbconnection_id INTEGER,
  photomultiplier_id INTEGER,
  setup_id INTEGER,
  run_id INTEGER  
) AS
$BODY$
BEGIN
  FOR tombinput_id, trbtombconnection_id, trboutput_id, trbinput_id, kbtrbconnection_id, konradboardoutput_id, konradboardinput_id, pmkbconnection_id, photomultiplier_id, setup_id, run_id IN
    SELECT 
      "TOMBInput".id AS tombinput_id,
      "TRBTOMBConnection".id AS trbtombconnection_id,
      "TRBOutput".id AS trboutput_id,
      "TRBInput".id AS trbinput_id,
      "KBTRBConnection".id AS kbtrbconnection_id,
      "KonradBoardOutput".id AS konradboardoutput_id,
      "KonradBoardInput".id AS konradboardinput_id,
      "PMKBConnection".id AS pmkbconnection_id,
      "PhotoMultiplier".id AS photomultiplier_id,
      "Setup".id AS setup_id,
      "Run".id AS run_id
    FROM "TOMBInput" 
      INNER JOIN "TRBTOMBConnection" ON "TOMBInput".id = "TRBTOMBConnection".tombinput_id 
      INNER JOIN "TRBOutput" ON "TRBTOMBConnection".trboutput_id = "TRBOutput".id
      INNER JOIN "TRBInput" ON "TRBOutput".trbinput_id = "TRBInput".id
      INNER JOIN "KBTRBConnection" ON "TRBInput".id = "KBTRBConnection".trbinput_id
      INNER JOIN "KonradBoardOutput" ON "KBTRBConnection".konradboardoutput_id = "KonradBoardOutput".id
      INNER JOIN "KonradBoardInput" ON "KonradBoardOutput".konradboardinput_id = "KonradBoardInput".id
      INNER JOIN "PMKBConnection" ON "KonradBoardInput".id = "PMKBConnection".konradboardinput_id
      INNER JOIN "PhotoMultiplier" ON "PMKBConnection".photomultiplier_id = "PhotoMultiplier".id
      INNER JOIN "Setup" ON "TRBTOMBConnection".setup_id = "Setup".id
      INNER JOIN "Run" ON "Setup".id = "Run".id
    AND
      "Run".id = p_run_id
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM photomultiplierIdBasedOnTOMBInputIdFunction(1);

7)
CREATE OR REPLACE FUNCTION tombinputIdBasedOnTRBIdAndTRBoutputIdFunction(IN p_run_id INTEGER)
RETURNS TABLE
(
  trb_id INTEGER,
  trboutput_id INTEGER,
  trbtombconnection_id INTEGER,
  tombinput_id INTEGER,
  setup_id INTEGER,
  run_id INTEGER  
) AS
$BODY$
BEGIN
  FOR trb_id, trboutput_id, trbtombconnection_id, tombinput_id, setup_id, run_id IN
    SELECT
      "TRB".id AS trb_id,
      "TRBOutput".id AS trboutput_id,
      "TRBTOMBConnection".id AS trbtombconnection_id,
      "TOMBInput".id AS tombinput_id,
      "Setup".id AS setup_id,
      "Run".id AS run_id
    FROM "TRB"
      INNER JOIN "TRBOutput" ON "TRB".id = "TRBOutput".trb_id
      INNER JOIN "TRBTOMBConnection" ON "TRBOutput".id = "TRBTOMBConnection".trboutput_id
      INNER JOIN "TOMBInput" ON "TRBTOMBConnection".tombinput_id = "TOMBInput".id
      INNER JOIN "Setup" ON "TRBTOMBConnection".setup_id = "Setup".id
      INNER JOIN "Run" ON "Setup".id = "Run".id
    AND
      "Run".id = p_run_id
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM tombinputIdBasedOnTRBIdAndTRBoutputIdFunction(1);

8)
CREATE OR REPLACE FUNCTION passedInformationIsTimeBasedOnTOMBInputIdFunction(IN p_run_id INTEGER)
RETURNS TABLE
(
  tombinput_id INTEGER,
  trbtombconnection_id INTEGER,
  trboutput_id INTEGER,
  trbinput_id INTEGER,
  kbtrbconnection_id INTEGER,
  konradboardoutput_id INTEGER,
  konradBoardOutput_passedinformationistime BOOLEAN,
  setup_id INTEGER,
  run_id INTEGER  
) AS
$BODY$
BEGIN
  FOR tombinput_id, trbtombconnection_id, trboutput_id, trbinput_id, kbtrbconnection_id, konradboardoutput_id, konradBoardOutput_passedinformationistime, setup_id, run_id IN
    SELECT
      "TOMBInput".id AS tombinput_id,
      "TRBTOMBConnection".id AS trbtombconnection_id,
      "TRBOutput".id AS trboutput_id,
      "TRBInput".id AS trbinput_id,
      "KBTRBConnection".id AS kbtrbconnection_id,
      "KonradBoardOutput".id AS konradboardoutput_id,
      "KonradBoardOutput".passedinformationistime AS konradBoardOutput_passedinformationistime,
      "Setup".id AS setup_id,
      "Run".id AS run_id
    FROM "TOMBInput" 
      INNER JOIN "TRBTOMBConnection" ON "TOMBInput".id = "TRBTOMBConnection".tombinput_id 
      INNER JOIN "TRBOutput" ON "TRBTOMBConnection".trboutput_id = "TRBOutput".id
      INNER JOIN "TRBInput" ON "TRBOutput".trbinput_id = "TRBInput".id
      INNER JOIN "KBTRBConnection" ON "TRBInput".id = "KBTRBConnection".trbinput_id
      INNER JOIN "KonradBoardOutput" ON "KBTRBConnection".konradboardoutput_id = "KonradBoardOutput".id
      INNER JOIN "Setup" ON "TRBTOMBConnection".setup_id = "Setup".id
      INNER JOIN "Run" ON "Setup".id = "Run".id
    AND
      "Run".id = p_run_id      
  LOOP
    RETURN NEXT;
  END LOOP;
END
$BODY$ LANGUAGE plpgsql STABLE;

SELECT * FROM passedInformationIsTimeBasedOnTOMBInputIdFunction(1);
