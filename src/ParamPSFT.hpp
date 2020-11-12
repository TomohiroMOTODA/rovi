#pragma once
#include "ParamPhaseMatching.hpp"
#include <map>

#if 0
#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <math.h>
#endif

#ifndef M_PI_2
#define M_PI_2	(0.5 * M_PI)
#endif
#endif

#ifdef YAML_PARAM
#include <yaml-cpp/yaml.h>
#endif

/**
 * �O���C�R�[�h�{�ʑ��V�t�g�p�����[�^
 */
struct GPhaseDecodeParameter : public PhaseMatchingParameter {
	int datatype;			///< ���͂��摜�̏ꍇ = 0, ���͂������摜���ʑ��E�O���C�R�[�h�f�[�^�̏ꍇ = 1, ���̑��̓G���[

	int bw_diff;			///< ���Í�[�P�x��].�S�_���摜-�S�����摜�̋P�x�����A���̒l�����ł���Όv�Z���珜�O�����.
	int brightness;			///< �S�_���摜�ɂ����ăn���[�V�����C���Ő��x�̏o�Ȃ��_��臒l[�P�x].���̒l�����傫�ȉ�f�͏��O�����.
	int darkness;			///< �S�_���摜�ɂ����ĈÂ��Đ��x�̏o�Ȃ��_�������l[�P�x].���̒l���������ȉ�f�͏��O�����.

	int phase_wd_min;		///< �摜���̈�������̍ŏ���(��f��). ���̒l�������������̋�Ԃ͊m���ȃf�[�^�Ƃ��Ȃ�.�����ɂ������ꍇ��0���w�肷�邱��.
	int phase_wd_thr;		///< �S�~�Ƃ��Ď̂Ă��Ԃ̍ő啝. ���̒l�ȉ��̋�Ԃ͎̂Ă���.�����ɂ������ꍇ��0�ɂ��邱��.
	int gcode_variation;	///< ���ԂɊ܂܂��O���C�R�[�h��ސ��̍ő�l. 1�ȏ�3�ȉ�

	GPhaseDecodeParameter() 
		: PhaseMatchingParameter(), datatype(0),
		bw_diff(16), brightness(256), darkness(15),
		phase_wd_min(8), phase_wd_thr(3), gcode_variation(3)
	{
	}

	GPhaseDecodeParameter(const GPhaseDecodeParameter &obj) {
		this->datatype = obj.datatype;

		this->bw_diff = obj.bw_diff;
		this->brightness = obj.brightness;
		this->darkness = obj.darkness;

		this->phase_wd_min = obj.phase_wd_min;
		this->phase_wd_thr = obj.phase_wd_thr;
		this->gcode_variation = obj.gcode_variation;
	}

	GPhaseDecodeParameter operator=(const GPhaseDecodeParameter &obj) {
		PhaseMatchingParameter::operator=(obj);

		this->datatype = obj.datatype;

		this->bw_diff = obj.bw_diff;
		this->brightness = obj.brightness;
		this->darkness = obj.darkness;

		this->phase_wd_min = obj.phase_wd_min;
		this->phase_wd_thr = obj.phase_wd_thr;
		this->gcode_variation = obj.gcode_variation;
		return *this;
	}

	void set(std::map<std::string, double> &params) {
		reinterpret_cast<PhaseMatchingParameter*>(this)->set(params);

		if (params.count("datatype")) this->datatype = (int)params["datatype"];

		if (params.count("bw_diff")) this->bw_diff = (int)params["bw_diff"];
		if (params.count("brightness")) this->brightness = (int)params["brightness"];
		if (params.count("darkness")) this->darkness = (int)params["darkness"];

		if (params.count("phase_wd_min")) this->phase_wd_min = (int)params["phase_wd_min"];
		if (params.count("phase_wd_thr")) this->phase_wd_thr = (int)params["phase_wd_thr"];
		if (params.count("gcode_variation")) this->gcode_variation = (int)params["gcode_variation"];
	}

#ifdef YAML_PARAM
	void set(const YAML::Node &params) {
		reinterpret_cast<PhaseMatchingParameter*>(this)->set(params);

		if (params["datatype"]) this->datatype = params["datatype"].as<int>();

		if (params["bw_diff"]) this->bw_diff = params["bw_diff"].as<int>();
		if (params["brightness"]) this->brightness = params["brightness"].as<int>();
		if (params["darkness"]) this->darkness = params["darkness"].as<int>();

		if (params["phase_wd_min"]) this->phase_wd_min = params["phase_wd_min"].as<int>();
		if (params["phase_wd_thr"]) this->phase_wd_thr = params["phase_wd_thr"].as<int>();
		if (params["gcode_variation"]) this->gcode_variation = params["gcode_variation"].as<int>();
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

		// ���̒l�͎󂯕t���Ȃ�
		if (phase_wd_min < 0) return false;
		if (phase_wd_thr < 0) return false;
		if (gcode_variation < 1) return false;

		return true;
	}
};



