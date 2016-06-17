#ifndef _____CALIBRATION_HEADER____________
#	define _____CALIBRATION_HEADER____________
#include <string>
#include <vector>
#include <functional>
#include <pqxx/pqxx>
class TFormula;
namespace JPetCalibration{
	using namespace std;
	using namespace pqxx;
	class CalibrationType{
	public:
		CalibrationType(const result::const_iterator&row);
		CalibrationType(const string&n,const size_t count,const string&f);
		CalibrationType(const string&&n,const size_t count,const string&&f);
		CalibrationType(const CalibrationType&source);
		~CalibrationType();
		const size_t id()const;
		const string&name()const;
		const size_t param_count()const;
		const string&formula()const;
	private:
		size_t m_id,m_count;
		string m_name,m_formula;
	};
	class CalibrationTypeEdit{
	public:
		CalibrationTypeEdit();
		virtual ~CalibrationTypeEdit();
		const vector<CalibrationType> GetTypes()const;
		void AddType(const CalibrationType&type);
		void AddType(const CalibrationType&&type);
	};
	
	typedef vector<size_t> id_set;
	typedef vector<double> parameter_set;
	class Calibration{
	public:
		Calibration(const result::const_iterator&row,const vector<string>&field_names);
		virtual ~Calibration();
		const string&name()const;
		const string&formula()const;
		const vector<double>&params()const;
		const string&encoded_params()const;
		double operator()(const parameter_set&X)const;
		double operator()(const parameter_set&&X)const;
	protected:
		Calibration(const CalibrationType&type,const parameter_set&values);
		Calibration(const Calibration&source);
	private:
		Calibration(const string& n,const size_t count,const string& f,const string&params);
		Calibration(const string&&n,const size_t count,const string&&f,const string&&params);
		string m_name,m_formula,m_encoded_params;
		parameter_set m_params;
		TFormula*m_tformula;
		double*buf;
		void init_formula();
		void deinit_formula();
	};
	class CalibrationForEquipment:public Calibration{
	public:
		CalibrationForEquipment(const id_set&eq_id,const result::const_iterator&row,const vector<string>&field_names);
		CalibrationForEquipment(const id_set&eq_id,const result::const_iterator&row,const vector<string>&&field_names);
		CalibrationForEquipment(const id_set&eq_id,const CalibrationType&type,const parameter_set&values);
		CalibrationForEquipment(const id_set&eq_id,const CalibrationType&type,const parameter_set&&values);
		CalibrationForEquipment(const CalibrationForEquipment&source);
		virtual ~CalibrationForEquipment();
		const size_t calibration_id()const;
		const size_t type_id()const;
		const id_set&equipment_ids()const;
	private:
		size_t m_type_id,m_cal_id;
		id_set m_eq_id;
	};
	class CalibrationForEquipmentAndRun:public Calibration{
	public:
		CalibrationForEquipmentAndRun(const id_set&eq_id,size_t run_id,const result::const_iterator&row,const vector<string>&field_names);
		CalibrationForEquipmentAndRun(const id_set&eq_id,size_t run_id,const result::const_iterator&row,const vector<string>&&field_names);
		CalibrationForEquipmentAndRun(const CalibrationForEquipmentAndRun&source);
		virtual ~CalibrationForEquipmentAndRun();
		const size_t run_id()const;
		const id_set&equipment_ids()const;
	private:
		size_t m_run_id;
		id_set m_eq_id;
	};
	class ICalibrationEditting{
	public:
		virtual const vector<CalibrationForEquipment> CalibrationList(const id_set&&eq_id)const=0;
		virtual const vector<CalibrationForEquipmentAndRun> CalibrationList(const id_set&&eq_id,const size_t run_id)const=0;
		virtual bool AddCalibration(const CalibrationForEquipment&&new_calibration)=0;
		virtual bool ConnectCalibrationToRun(const CalibrationForEquipment&cal,const size_t run_id)=0;
	};
	class ICalibrationObtaining{
	public:
		virtual const vector<CalibrationForEquipmentAndRun> ForRun(const size_t run_id)const=0;
	};
	
	class AmplificationCalibrationEdit:public ICalibrationEditting{
	public:
		AmplificationCalibrationEdit();
		virtual ~AmplificationCalibrationEdit();
		virtual const vector<CalibrationForEquipment> CalibrationList(const id_set&&eq_id)const override;
		virtual const vector<CalibrationForEquipmentAndRun> CalibrationList(const id_set&&eq_id,const size_t setup_id)const override;
		virtual bool AddCalibration(const CalibrationForEquipment&&new_calibration)override;
		virtual bool ConnectCalibrationToRun(const CalibrationForEquipment&cal,const size_t run_id)override;
	private:
		vector<string> m_fields;
	};
	class AmplificationCalibration:public ICalibrationObtaining{
	public:
		AmplificationCalibration();
		virtual ~AmplificationCalibration();
		virtual const vector<CalibrationForEquipmentAndRun> ForRun(const size_t run_id)const override;
	private:
		vector<string> m_fields;
	};
};
#endif
