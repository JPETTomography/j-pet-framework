#ifdef __CINT__

#pragma link off all globals;
#pragma link off all classes;
#pragma link off all functions;

#pragma link C++ nestedclasses;

#pragma link C++ function JPetWriter::Write(JPetChannel&);
#pragma link C++ function JPetWriter::Write(vector <JPetChannel>&);
#pragma link C++ function JPetWriter::Write(JPetDataModule&);
#pragma link C++ function JPetWriter::Write(vector <JPetDataModule>&);
#pragma link C++ function JPetWriter::Write(JPetDataSource&);
#pragma link C++ function JPetWriter::Write(vector <JPetDataSource>&);
#pragma link C++ function JPetWriter::Write(JPetLayer&);
#pragma link C++ function JPetWriter::Write(vector <JPetLayer>&);
#pragma link C++ function JPetWriter::Write(JPetMatrix&);
#pragma link C++ function JPetWriter::Write(vector <JPetMatrix>&);
#pragma link C++ function JPetWriter::Write(JPetPM&);
#pragma link C++ function JPetWriter::Write(vector <JPetPM>&);
#pragma link C++ function JPetWriter::Write(JPetScin&);
#pragma link C++ function JPetWriter::Write(vector <JPetScin>&);
#pragma link C++ function JPetWriter::Write(JPetSetup&);
#pragma link C++ function JPetWriter::Write(vector <JPetSetup>&);
#pragma link C++ function JPetWriter::Write(JPetSlot&);
#pragma link C++ function JPetWriter::Write(vector <JPetSlot>&);

#pragma link C++ function JPetWriter::Write(JPetBaseHit);
#pragma link C++ function JPetWriter::Write(vector <JPetBaseHit>&);
#pragma link C++ function JPetWriter::Write(JPetMCRecoHit&);
#pragma link C++ function JPetWriter::Write(vector <JPetMCRecoHit>&);
#pragma link C++ function JPetWriter::Write(JPetPhysRecoHit&);
#pragma link C++ function JPetWriter::Write(vector <JPetPhysRecoHit>&);
#pragma link C++ function JPetWriter::Write(JPetRecoHit&);
#pragma link C++ function JPetWriter::Write(vector <JPetRecoHit>&);
#pragma link C++ function JPetWriter::Write(JPetEvent&);
#pragma link C++ function JPetWriter::Write(vector <JPetEvent>&);
#pragma link C++ function JPetWriter::Write(JPetLOR&);
#pragma link C++ function JPetWriter::Write(vector <JPetLOR>&);
#pragma link C++ function JPetWriter::Write(JPetTimeWindow&);
#pragma link C++ function JPetWriter::Write(vector <JPetTimeWindow>&);
#pragma link C++ function JPetWriter::Write(JPetBaseSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetBaseSignal>&);
#pragma link C++ function JPetWriter::Write(JPetChannelSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetChannelSignal>&);
#pragma link C++ function JPetWriter::Write(JPetMatrixSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetMatrixSignal>&);
#pragma link C++ function JPetWriter::Write(JPetPhysSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetPhysSignal>&);
#pragma link C++ function JPetWriter::Write(JPetPMSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetPMSignal>&);
#pragma link C++ function JPetWriter::Write(JPetRecoSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetRecoSignal>&);
#pragma link C++ function JPetWriter::Write(JPetShapedSignal&);
#pragma link C++ function JPetWriter::Write(vector <JPetShapedSignal>&);
#pragma link C++ function JPetWriter::Write(JPetRawMCHit&);
#pragma link C++ function JPetWriter::Write(vector <JPetRawMCHit>&);

#pragma link C++ class JPetParamBank + ;
#pragma link C++ class JPetTreeHeader + ;
#pragma link C++ class JPetStatistics + ;

#pragma link C++ class JPetChannel + ;
#pragma link C++ class JPetDataModule + ;
#pragma link C++ class JPetDataSource + ;
#pragma link C++ class JPetLayer + ;
#pragma link C++ class JPetMatrix + ;
#pragma link C++ class JPetPM + ;
#pragma link C++ class JPetScin + ;
#pragma link C++ class JPetSetup + ;
#pragma link C++ class JPetSlot + ;

#pragma link C++ class JPetBaseHit + ;
#pragma link C++ class JPetMCRecoHit + ;
#pragma link C++ class JPetPhysSignal + ;
#pragma link C++ class JPetRecoSignal + ;
#pragma link C++ class JPetEvent + ;
#pragma link C++ class JPetLOR + ;
#pragma link C++ class JPetTimeWindow + ;
#pragma link C++ class JPetBaseSignal + ;
#pragma link C++ class JPetChannelSignal + ;
#pragma link C++ class JPetMatrixSignal + ;
#pragma link C++ class JPetPhysRecoHit + ;
#pragma link C++ class JPetPMSignal + ;
#pragma link C++ class JPetRecoHit + ;
#pragma link C++ class JPetShapedSignal + ;

#pragma link C++ class JPetMCDecayTree + ;
#pragma link C++ class JPetRawMCHit + ;
#pragma link C++ class JPetTimeWindowMC + ;

#pragma link C++ class JPetGeantDecayTree + ;
#pragma link C++ class JPetGeantEventInformation + ;
#pragma link C++ class JPetGeantEventPack + ;
#pragma link C++ class JPetGeantScinHits + ;

#pragma link C++ struct JPetTreeHeader::ProcessingStageInfo + ;
#pragma link C++ struct shapePoint + ;

#pragma link C++ enum JPetPhysRecoHit::Signal;
#pragma link C++ enum JPetRecoHit::RecoFlag;
#pragma link C++ enum JPetEvent::RecoFlag;
#pragma link C++ enum JPetLOR::RecoFlag;
#pragma link C++ enum JPetChannelSignal::EdgeType;
#pragma link C++ enum JPetPMSignal::PointsSortOrder;
#pragma link C++ enum JPetRecoSignal::RecoFlag;

#pragma link C++ enum JPetSlot::Type;
#pragma link C++ enum JPetMatrix::Side;

#endif
