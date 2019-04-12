#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;

#pragma link C++ function JPetWriter::Write(JPetBarrelSlot&);
#pragma link C++ function JPetWriter::Write(vector <JPetBarrelSlot>&);
#pragma link C++ function JPetWriter::Write(JPetLOR&);
#pragma link C++ function JPetWriter::Write(vector <JPetLOR>&);
#pragma link C++ function JPetWriter::Write(JPetHit&);
#pragma link C++ function JPetWriter::Write(vector <JPetHit>&);
#pragma link C++ function JPetWriter::Write(JPetPM&);
#pragma link C++ function JPetWriter::Write(vector <JPetPM>&);
#pragma link C++ function JPetWriter::Write(JPetScin&);
#pragma link C++ function JPetWriter::Write(vector <JPetScin>&);
#pragma link C++ function JPetWriter::Write(JPetSigCh&);
#pragma link C++ function JPetWriter::Write(vector <JPetSigCh>&);
#pragma link C++ function JPetWriter::Write(JPetRawSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetRawSignal>&);
#pragma link C++ function JPetWriter::Write(JPetTRB&);
#pragma link C++ function JPetWriter::Write(vector <JPetTRB>&);
#pragma link C++ function JPetWriter::Write(JPetTimeWindow&);
#pragma link C++ function JPetWriter::Write(vector <JPetTimeWindow>&);

#pragma link C++ class JPetParamBank + ;
#pragma link C++ class JPetFEB + ;
#pragma link C++ class JPetScin + ;
#pragma link C++ class JPetRecoSignal + ;
#pragma link C++ class JPetBaseSignal + ;
#pragma link C++ class JPetRawSignal + ;
#pragma link C++ class JPetPhysSignal + ;
#pragma link C++ class JPetSigCh + ;
#pragma link C++ class JPetTreeHeader + ;
#pragma link C++ class JPetHit + ;
#pragma link C++ class JPetTimeWindowMC + ;
#pragma link C++ class JPetFrame + ;
#pragma link C++ class JPetPM + ;
#pragma link C++ class JPetTOMBChannel + ;
#pragma link C++ class JPetEvent + ;
#pragma link C++ class JPetLOR + ;
#pragma link C++ class JPetGeantEventPack + ;
#pragma link C++ class JPetMCDecayTree + ;
#pragma link C++ class JPetTimeWindow + ;
#pragma link C++ class JPetGeantScinHits + ;
#pragma link C++ class JPetStatistics + ;
#pragma link C++ class JPetTRB + ;
#pragma link C++ class JPetBarrelSlot + ;
#pragma link C++ class JPetGeantDecayTree + ;
#pragma link C++ class JPetLayer + ;
#pragma link C++ class JPetGeantEventInformation + ;
#pragma link C++ class JPetMCHit + ;

#pragma link C++ enum JPetBaseSignal::RecoFlag;
#pragma link C++ enum JPetSigCh::RecoFlag;
#pragma link C++ enum JPetSigCh::EdgeType;

#pragma link C++ struct shapePoint + ;
#pragma link C++ struct JPetScin::ScinDimensions + ;
#pragma link C++ struct JPetTreeHeader::ProcessingStageInfo + ;

#endif