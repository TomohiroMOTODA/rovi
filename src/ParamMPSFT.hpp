#pragma once

#include "ParamPhaseMatching.hpp"
#include <map>

#ifdef YAML_PARAM
#include <yaml-cpp/yaml.h>
#endif


/**
 * ���ʑ��V�t�g�p�����[�^
 */
struct MPhaseDecodeParameter : public PhaseMatchingParameter {
	int datatype;		///< ���͂��摜�̏ꍇ = 0, ���͂������摜���ʑ��f�[�^�̏ꍇ = 1, ���̑��̓G���[

	int bw_diff;		///< �P�x��臒l(���̒l�����̉�f�͏����ΏۂƂ��Ȃ�)
	int brightness;		///< �ő�P�x�l(���̒l�ȏ�̉�f�͏����ΏۂƂ��Ȃ�)
	int darkness;		///< �ŏ��P�x�l(���̒l�ȉ��̉�f�͏����ΏۂƂ��Ȃ�)

	int n_phaseshift;	///< �ʑ��̃V�t�g��
	int n_periods;		///< �����̐�(��ސ�)
	int period[4];		///< period[i] : i�Ԗڂ̎����̒l

	MPhaseDecodeParameter() : PhaseMatchingParameter(), datatype(0), n_phaseshift(4), n_periods(3),
		bw_diff(16), brightness(256), darkness(15)
	{
		period[0] =  9;
		period[1] = 10;
		period[2] = 11;
		period[3] = 12;
	}

	MPhaseDecodeParameter(const MPhaseDecodeParameter &obj) {
		this->datatype = obj.datatype;

		this->bw_diff = obj.bw_diff;
		this->brightness = obj.brightness;
		this->darkness = obj.darkness;

		this->n_phaseshift = obj.n_phaseshift;
		this->n_periods = obj.n_periods;
		this->period[0] = obj.period[0];
		this->period[1] = obj.period[1];
		this->period[2] = obj.period[2];
		this->period[3] = obj.period[3];
	}

	MPhaseDecodeParameter operator=(const MPhaseDecodeParameter &obj) {
		PhaseMatchingParameter::operator=(obj);

		this->datatype = obj.datatype;

		this->bw_diff = obj.bw_diff;
		this->brightness = obj.brightness;
		this->darkness = obj.darkness;

		this->n_phaseshift = obj.n_phaseshift;
		this->n_periods = obj.n_periods;
		this->period[0] = obj.period[0];
		this->period[1] = obj.period[1];
		this->period[2] = obj.period[2];
		this->period[3] = obj.period[3];

		return *this;
	}

	void set(std::map<std::string, double> &params) {
		reinterpret_cast<PhaseMatchingParameter*>(this)->set(params);

		if (params.count("datatype")) this->datatype = (int)params["datatype"];

		if (params.count("brightness")) this->brightness = (int)params["brightness"];
		if (params.count("darkness")) this->darkness = (int)params["darkness"];
		if (params.count("bw_diff")) this->bw_diff = (int)params["bw_diff"];

		if (params.count("n_phaseshift")) this->n_phaseshift = (int)params["n_phaseshift"];
		if (params.count("n_periods")) this->n_periods = (int)params["n_periods"];
		if (params.count("period0")) this->period[0] = (int)params["period0"];
		if (params.count("period1")) this->period[1] = (int)params["period1"];
		if (params.count("period2")) this->period[2] = (int)params["period2"];
		if (params.count("period3")) this->period[3] = (int)params["period3"];
	}
#ifdef YAML_PARAM
	void set(const YAML::Node &params) {
		reinterpret_cast<PhaseMatchingParameter*>(this)->set(params);
		if (params["datatype"]) this->datatype = params["datatype"].as<int>();

		if (params["brightness"]) this->brightness = params["brightness"].as<int>();
		if (params["darkness"]) this->darkness = params["darkness"].as<int>();
		if (params["bw_diff"]) this->bw_diff = params["bw_diff"].as<int>();

		if (params["n_phaseshift"]) this->n_phaseshift = params["n_phaseshift"].as<int>();

		if (params["periods"]) {
			this->n_periods = params["periods"].size();
			for (int n = 0; n < this->n_periods; n++) {
				this->period[n] = params["periods"][n].as<int>();
			}
		}
	}
#endif

	/**
	 * �p�����[�^���A���S���Y���̋��e�͈͂Ɏ��܂��Ă��邩�ǂ������`�F�b�N����.
	 * @return ���Ȃ����true, ��肠���false.
	 */
	bool check(void) const {
		if (!PhaseMatchingParameter::check()) return false;
		// �摜���ʑ��f�[�^���w�肳��Ă��Ȃ���Αʖ�
		if (datatype != 0 && datatype != 1) return false;

		// ���̏��A�V�t�g����3 or 4�����Ή����Ă��Ȃ�
		if (n_phaseshift == 3 || n_phaseshift == 4) {}
		else return false;

		// �����̑g�ݍ��킹��4�܂�(�w�b�_�̓s����)
		if (n_periods > 4) return false;
		return true;
	}
};
