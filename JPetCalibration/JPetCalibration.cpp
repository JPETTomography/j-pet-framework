#include <exception>
#include <iostream>
#include <sstream>
#include <TFormula.h>
#include <pqxx/pqxx>
#include "../DBHandler/HeaderFiles/DBHandler.h"
#include "JPetCalibration.h"
namespace JPetCalibration {
	using namespace std;
	class Exception:public exception{
	public:
		Exception(const string&&msg);
		virtual ~Exception() throw();
		virtual const char* what() const throw();
	private:
		string m_msg;
	};

	using namespace std;
	using namespace pqxx;
	using namespace DB::SERVICES;
	Exception::Exception(const string&& msg):m_msg(msg){}
	Exception::~Exception()throw(){}
	const char* Exception::what() const throw(){
		return m_msg.c_str();
	}

	CalibrationType::CalibrationType(const CalibrationType& source)
	:m_id(source.m_id), m_count(source.m_count), m_name(source.m_name),m_formula(source.m_formula){}

	CalibrationType::CalibrationType(const result::const_iterator&row)
	:m_id(row["type_id"].as<size_t>()), m_count(row["param_count"].as<size_t>()),
  m_name(row["name"].as<string>()), m_formula(row["formula"].as<string>()){}

	CalibrationType::CalibrationType(const string& n,const size_t count, const string& f)
	:m_id(0), m_count(count), m_name(n), m_formula(f){}

	CalibrationType::CalibrationType(const string&&n,const size_t count,const string&&f)
	:m_id(0), m_count(count), m_name(n), m_formula(f){}

	CalibrationType::~CalibrationType(){}
	const size_t CalibrationType::id()const{return m_id;}
	const string& CalibrationType::name()const{return m_name;}
	const size_t CalibrationType::param_count()const{return m_count;}
	const string& CalibrationType::formula()const{return m_formula;}

	CalibrationTypeEdit::CalibrationTypeEdit(){}
	CalibrationTypeEdit::~CalibrationTypeEdit(){}
	const vector<CalibrationType> CalibrationTypeEdit::GetTypes()const{
		result data=DBHandler::getInstance().querry("SELECT * FROM getcalibrationtypes();");
		vector<CalibrationType> res;
		for(const auto&row:data)res.push_back(CalibrationType(row));
		return res;
	}
	void CalibrationTypeEdit::AddType(const CalibrationType& type){
		if(type.id()>0)throw Exception("CalibrationInterface: attempt to insert CalibrationType that already exists");
		string req="SELECT * FROM insert_calibrationtype(";
		req+="'"+type.name()+"',"+to_string(type.param_count())+",'"+type.formula()+"');";
		DBHandler::getInstance().querry(req);
	}
	void CalibrationTypeEdit::AddType(const CalibrationType&& type){AddType(type);}


	Calibration::Calibration(const string&n,const size_t count,const string& f,const string&params)
	:m_name(n),m_formula(f),m_encoded_params(params){
		stringstream ss(params);
		vector<string> tokens;
		copy(istream_iterator<string>(ss),
		     istream_iterator<string>(),
		     back_inserter(tokens));
		for(const string&token:tokens)
			if(m_params.size()<count)
				m_params.push_back(stod(token));
		if(m_params.size()<count)
			throw Exception("PhmAmplCalibration: the number of decoded parameters is bad");
		init_formula();
	}
	Calibration::Calibration(const string&&n,const size_t count,const string&&f,const string&&params):Calibration(n,count,f,params){}
	Calibration::Calibration(const result::const_iterator&row,const vector<string>&field_names)
	:Calibration(row[field_names[0]].as<string>(),row[field_names[1]].as<size_t>(),row[field_names[2]].as<string>(),row[field_names[3]].as<string>()){}
	Calibration::Calibration(const CalibrationType&type,const parameter_set&values):m_name(type.name()),m_formula(type.formula()){
		if(0==type.id())throw Exception("Calibration: attempt to create calibration of type that is not present in database");
		if(values.size()!=type.param_count())
			throw Exception("Calibration: parameters count is not good for selected calibration type");
		m_encoded_params="";
		for(double p:values){
			m_params.push_back(p);
			m_encoded_params+=to_string(p)+" ";
		}
		init_formula();
	}
	Calibration::Calibration(const Calibration& source)
	:m_name(source.m_name),m_formula(source.m_formula),m_encoded_params(source.m_encoded_params){
		for(double p:source.m_params)m_params.push_back(p);
		init_formula();
	}
	Calibration::~Calibration(){deinit_formula();}
	const string& Calibration::name() const{return m_name;}
	const string& Calibration::formula() const{return m_formula;}
	const vector<double>&Calibration::params() const{return m_params;}
	const string& Calibration::encoded_params() const{return m_encoded_params;}
	void Calibration::init_formula(){
		buf=new double[m_params.size()];
		for(size_t i=0;i<m_params.size();i++)buf[i]=m_params[i];
		m_tformula= new TFormula(formula().c_str(),formula().c_str());
	}
	void Calibration::deinit_formula(){
		delete[] buf;
		delete m_tformula;
	}
	double Calibration::operator()(const parameter_set& X) const{
		double x[X.size()];
		for(size_t i=0,n=X.size();i<n;i++)x[i]=X[i];
		return m_tformula->EvalPar(x,buf);
	}
	double Calibration::operator()(const parameter_set&& X) const{return operator()(X);}


	CalibrationForEquipment::CalibrationForEquipment(const id_set&eq_id,const result::const_iterator&row,const vector<string>&field_names)
	:Calibration(row, field_names), m_type_id(0), m_cal_id(0){for(const auto&item:eq_id)m_eq_id.push_back(item);}
	CalibrationForEquipment::CalibrationForEquipment(const id_set&eq_id,const result::const_iterator&row,const vector<string>&&field_names)
	:CalibrationForEquipment(eq_id,row,field_names){}
	CalibrationForEquipment::CalibrationForEquipment(const id_set&eq_id,const CalibrationType&type,const parameter_set&values)
	:Calibration(type, values), m_type_id(0), m_cal_id(0){for(const auto&item:eq_id)m_eq_id.push_back(item);}
	CalibrationForEquipment::CalibrationForEquipment(const id_set& eq_id,const CalibrationType&type,const parameter_set&&values)
	:CalibrationForEquipment(eq_id,type,values){}
	CalibrationForEquipment::CalibrationForEquipment(const CalibrationForEquipment&source)
	:Calibration(source),m_type_id(0), m_cal_id(0){for(const auto&item:source.m_eq_id)m_eq_id.push_back(item);}
	CalibrationForEquipment::~CalibrationForEquipment(){}

	const size_t CalibrationForEquipment::calibration_id()const{return m_cal_id;}
	const id_set& CalibrationForEquipment::equipment_ids()const{return m_eq_id;}
	const size_t CalibrationForEquipment::type_id()const{return m_type_id;}

	CalibrationForEquipmentAndRun::CalibrationForEquipmentAndRun(const id_set&eq_id,size_t run_id,const result::const_iterator&row,const vector<string>&field_names)
	:Calibration(row, field_names),m_run_id(run_id){for(const auto&item:eq_id)m_eq_id.push_back(item);}
	CalibrationForEquipmentAndRun::CalibrationForEquipmentAndRun(const id_set&eq_id,size_t run_id,const result::const_iterator&row,const vector<string>&&field_names)
	:CalibrationForEquipmentAndRun(eq_id,run_id,row,field_names){}
	CalibrationForEquipmentAndRun::CalibrationForEquipmentAndRun(const CalibrationForEquipmentAndRun& source)
	:Calibration(source),m_run_id(source.m_run_id){for(const auto&item:source.m_eq_id)m_eq_id.push_back(item);}
	CalibrationForEquipmentAndRun::~CalibrationForEquipmentAndRun(){}
	const id_set&CalibrationForEquipmentAndRun::equipment_ids()const{return m_eq_id;}
	const size_t CalibrationForEquipmentAndRun::run_id()const{return m_run_id;}

	AmplificationCalibrationEdit::AmplificationCalibrationEdit()
	:m_fields{"name","param_count","formula","param_values"}{}
	AmplificationCalibrationEdit::~AmplificationCalibrationEdit(){}
	const vector<CalibrationForEquipment> AmplificationCalibrationEdit::CalibrationList(const id_set&&eq_id)const{
		vector<CalibrationForEquipment> res;
		for(const auto&row:DBHandler::getInstance().querry("select * from getcalibrations_phmampl_allphm("+to_string(eq_id[0])+");"))
			res.push_back(CalibrationForEquipment(eq_id,row,m_fields));
		return res;
	}
	const vector<CalibrationForEquipmentAndRun> AmplificationCalibrationEdit::CalibrationList(const id_set&&eq_id,const size_t setup_id)const{
		vector<CalibrationForEquipmentAndRun> res;
		for(const auto&row:DBHandler::getInstance()
			.querry("select * from getcalibrations_phmampl_setupandphm("+to_string(setup_id)+","+to_string(eq_id[0])+");"))
			res.push_back(CalibrationForEquipmentAndRun(eq_id,setup_id,row,m_fields));
		return res;
	}
	bool AmplificationCalibrationEdit::AddCalibration(const CalibrationForEquipment&&new_calibration){
		if(
			(new_calibration.calibration_id()==0)&&
			(new_calibration.type_id()!=0)&&
			(new_calibration.equipment_ids()[0]!=0)
		){
			DBHandler::getInstance().querry("select * from insert_calibration_phmampl("
				+to_string(new_calibration.equipment_ids()[0])+","
				+to_string(new_calibration.type_id())+","
				+new_calibration.encoded_params()+");"
			);
			return true;
		}else return false;
	}
	bool AmplificationCalibrationEdit::ConnectCalibrationToRun(const CalibrationForEquipment&cal,const size_t run_id){
		if(
			(cal.calibration_id()!=0)&&(cal.type_id()==0)&&
			(cal.equipment_ids()[0]!=0)
		){
			DBHandler::getInstance().querry(
				"select * from connect_calibration_phmampl("
				+to_string(cal.calibration_id())+","+to_string(run_id)+");"
			);
			return true;
		}else return false;
	}

	AmplificationCalibration::AmplificationCalibration()
		:m_fields{"name","param_count","formula","param_values"}{}
	AmplificationCalibration::~AmplificationCalibration(){}
	const vector<CalibrationForEquipmentAndRun> AmplificationCalibration::ForRun(const size_t run_id) const{
		vector<CalibrationForEquipmentAndRun> res;
		for(const auto&row:
			DBHandler::getInstance().querry(
				"select * from getcalibrations_phmampl_run("+to_string(run_id)+");"
			)
		)
			res.push_back(CalibrationForEquipmentAndRun(
				{row["id_phm"].as<size_t>()},run_id,row,m_fields
			));
		return res;
	}


}
