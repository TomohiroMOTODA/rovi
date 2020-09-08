#pragma once
#include <map>

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#endif
#include <math.h>

#ifndef M_PI_2
#define M_PI_2	(0.5 * M_PI)
#endif

#ifdef YAML_PARAM
#include <yaml-cpp/yaml.h>
#endif

/**
 * �ʑ��}�b�`���O�p�����[�^
 */
struct PhaseMatchingParameter {
	double max_ph_diff;		///< �����v�Z���̍��E�J�����̍ő�ʑ���(������z���ʑ�����NG)[rad]	
	double max_parallax;	///< �ő压��[pixel]
	double min_parallax;	///< �ŏ�����[pixel]
	int ls_points;			///< ���������߂�ۂ̍ŏ����ߎ��_��[points](3 or 5)

	PhaseMatchingParameter() :
		max_ph_diff(M_PI_2), max_parallax(400), min_parallax(-300), ls_points(3) {}

	PhaseMatchingParameter(const PhaseMatchingParameter &obj) {
		this->max_ph_diff = obj.max_ph_diff;
		this->max_parallax = obj.max_parallax;
		this->min_parallax = obj.min_parallax;
		this->ls_points = obj.ls_points;
	}

	PhaseMatchingParameter operator=(const PhaseMatchingParameter &obj) {
		this->max_ph_diff = obj.max_ph_diff;
		this->max_parallax = obj.max_parallax;
		this->min_parallax = obj.min_parallax;
		this->ls_points = obj.ls_points;
		return *this;
	}

	void set(std::map<std::string, double> &params) {
		if (params.count("max_ph_diff")) this->max_ph_diff = params["max_ph_diff"];
		if (params.count("max_parallax")) this->max_parallax = params["max_parallax"];
		if (params.count("min_parallax")) this->min_parallax = params["min_parallax"];
		if (params.count("ls_points")) this->ls_points = (int)params["ls_points"];
	}

#ifdef YAML_PARAM
	void set(const YAML::Node &params) {
		this->max_ph_diff = params["max_ph_diff"].as<double>();
		this->max_parallax = params["max_parallax"].as<double>();
		this->min_parallax = params["min_parallax"].as<double>();
		this->ls_points = params["ls_points"].as<int>();
	}
#endif

	/**
	 * �p�����[�^���A���S���Y���̋��e�͈͂Ɏ��܂��Ă��邩�ǂ������`�F�b�N����.
	 * @return ���Ȃ����true, ��肠���false.
	 */
	bool check(void) const {
		// ����3 or 5�����Ή����Ă��Ȃ�
		if (this->ls_points == 3 || this->ls_points == 5) {}
		else return false;

		// �ő压��<�ŏ������ł���
		if (this->max_parallax < this->min_parallax) return false;
		return true;
	}
};
