#pragma once

#include <map>

#ifdef YAML_PARAM
#include <yaml-cpp/yaml.h>
#endif

/**
 * SGBM�p�����[�^
 */
struct SGBMParameter {
	int min_disparity;		///< ��蓾��ŏ��̎����l
	int num_disparities;	///< �����̑���(�K��16�̔{��)
	int blockSize;			///< �}�b�`���O�����u���b�N�̃T�C�Y(�K���)
	int P1;	///< �����̊��炩���𐧌䂷��p�����[�^1(�}�C�i�X��ݒ肵�Ă����ƑÓ��Ȓl������Ōv�Z���܂�)
	int P2;	///< �����̊��炩���𐧌䂷��p�����[�^2(P2 > P1)(�}�C�i�X��ݒ肵�Ă����ƑÓ��Ȓl������Ōv�Z���܂�)
	int disp12MaxDiff;		///< �����`�F�b�N�ɂ����鋖�e�����ő�̍�.�`�F�b�N���s��Ȃ��ꍇ��0�ȉ��̒l�Ƃ���.
	int preFilterCap;		///< ���O�t�B���^�ɂ����ĉ摜�s�N�Z����؂�̂Ă�臒l(x�����l�͈̔�)
	int uniquenessRatio;	///< �œK���͓�Ԗڂ̉��ɑ΂��āA�����Ŏw�肵���l�����R�X�g�֐��l���ǂ��Ȃ���΂Ȃ�Ȃ�(�p�[�Z���g�P��)
	int speckleWindowSize;	///< �m�C�Y�X�y�b�N���△���ȃs�N�Z�����l�����ꂽ���炩�Ȏ����̈�̍ő�T�C�Y.0�ɂ���ƃX�y�b�N���t�B���^�������ɂȂ�
	int speckleRange;		///< ���ꂼ��̘A�������ɂ�����ő压��(1or2���K�؂Ȓl)
	int mode;	///< SGBM�̃��[�h(0: MODE_SGBM, 1: MODE_HH, 2: MODE_SGBM_3WAY, 3: MODE_HH4. 1�ɂ���Ɗ��S��2�p�X���I�v��@�ɂĒT�����s��.���A�摜�T�C�Yx���������̃��������K�v�Ȃ̂Œ���)

	SGBMParameter() :
		min_disparity(0),
		num_disparities(256),
		blockSize(5),
		P1(-1),
		P2(-1),
		disp12MaxDiff(0),
		preFilterCap(0),
		uniquenessRatio(20),
		speckleWindowSize(100),
		speckleRange(1),
		mode(0)	{}

	SGBMParameter(const SGBMParameter &obj) {
		this->min_disparity = obj.min_disparity;
		this->num_disparities = obj.num_disparities;
		this->blockSize = obj.blockSize;
		this->P1 = obj.P1;
		this->P2 = obj.P2;
		this->disp12MaxDiff = obj.disp12MaxDiff;
		this->preFilterCap = obj.preFilterCap;
		this->uniquenessRatio = obj.uniquenessRatio;
		this->speckleWindowSize = obj.speckleWindowSize;
		this->speckleRange = obj.speckleRange;
		this->mode = obj.mode;
	}

	SGBMParameter operator=(const SGBMParameter &obj) {
		this->min_disparity = obj.min_disparity;
		this->num_disparities = obj.num_disparities;
		this->blockSize = obj.blockSize;
		this->P1 = obj.P1;
		this->P2 = obj.P2;
		this->disp12MaxDiff = obj.disp12MaxDiff;
		this->preFilterCap = obj.preFilterCap;
		this->uniquenessRatio = obj.uniquenessRatio;
		this->speckleWindowSize = obj.speckleWindowSize;
		this->speckleRange = obj.speckleRange;
		this->mode = obj.mode;
		return (*this);
	}

	void set(std::map<std::string, double> &params) {
		if (params.count("min_disparity")) this->min_disparity = (int)params["min_disparity"];
		if (params.count("num_disparities")) this->num_disparities = (int)params["num_disparities"];
		if (params.count("blockSize")) this->blockSize = (int)params["blockSize"];
		if (params.count("P1")) this->P1 = (int)params["P1"];
		if (params.count("P2")) this->P2 = (int)params["P2"];
		if (params.count("disp12MaxDiff")) this->disp12MaxDiff = (int)params["disp12MaxDiff"];
		if (params.count("preFilterCap")) this->preFilterCap = (int)params["preFilterCap"];
		if (params.count("uniquenessRatio")) this->uniquenessRatio = (int)params["uniquenessRatio"];
		if (params.count("speckleWindowSize")) this->speckleWindowSize = (int)params["speckleWindowSize"];
		if (params.count("speckleRange")) this->speckleRange = (int)params["speckleRange"];
		if (params.count("mode")) this->mode = (int)params["mode"];
	}

#ifdef YAML_PARAM
	void set(const YAML::Node &params) {
		if (params["min_disparity"]) this->min_disparity = params["min_disparity"].as<int>();
		if (params["num_disparities"]) this->num_disparities = params["num_disparities"].as<int>();
		if (params["blockSize"]) this->blockSize = params["blockSize"].as<int>();
		if (params["P1"]) this->P1 = params["P1"].as<int>();
		if (params["P2"]) this->P2 = params["P2"].as<int>();
		if (params["disp12MaxDiff"]) this->disp12MaxDiff = params["disp12MaxDiff"].as<int>();
		if (params["preFilterCap"]) this->preFilterCap = params["preFilterCap"].as<int>();
		if (params["uniquenessRatio"]) this->uniquenessRatio = params["uniquenessRatio"].as<int>();
		if (params["speckleWindowSize"]) this->speckleWindowSize = (int)params["speckleWindowSize"].as<int>();
		if (params["speckleRange"])	this->speckleRange = (int)params["speckleRange"].as<int>();
		if (params["mode"]) this->mode = (int)params["mode"].as<int>();
	}
#endif
	/**
	 * �p�����[�^���A���S���Y���̋��e�͈͂Ɏ��܂��Ă��邩�ǂ������`�F�b�N����.
	 * @return ���Ȃ����true, ��肠���false.
	 */
	bool check(void) const {
		if (num_disparities % 16 != 0) return false;
		if (blockSize % 2 != 1) return false;
		if (uniquenessRatio < 0 || uniquenessRatio > 100) return false;
		if (mode < 0 || mode > 3) return false;
		return true;
	}

	/**
	 * SGBM �̃p�����[�^ P1 �̒l��Ԃ�.
	 * @return P1�̒l
	 * @param [in] SGBM�Ώۂ̉摜�̃`�����l����
	 */
	int getP1(const int channels = 1) {
		if (this->P1 < 0) {
			// �����̊��炩���𐧌䂷��p�����[�^(�ׂ荇���s�N�Z���ԂŎ������}1�ŕω������ꍇ�̃y�i���e�B)
			return 8 * this->blockSize * this->blockSize * channels;
		}
		else return this->P1;
	}

	/**
	 * SGBM �̃p�����[�^ P2 �̒l��Ԃ�.
	 * @return P2�̒l
	 * @param [in] SGBM�Ώۂ̉摜�̃`�����l����
	 */
	int getP2(const int channels = 1) {
		if (this->P2 < 0) {
			// �����̊��炩���𐧌䂷��p�����[�^(�ׂ荇���s�N�Z���ԂŎ�����1�����傫���ω������ꍇ�̃y�i���e�B
			return 32 * this->blockSize * this->blockSize * channels;
		}
		else return this->P2;
	}
};
