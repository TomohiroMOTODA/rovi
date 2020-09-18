#pragma once

#include <string>
#include "iCalibBoardRecognizer.hpp"


/// �J�����L�����u�p�����[�^�^
struct CameraCalibParam {
	double leng;	///< �œ_����
	double cell;	///< �Z���T�[�Z���T�C�Y
	double F;				///< �J�����p�����[�^F�l
	int calibration_flags;	///< cv::cameraCalibrate�̃t���O�l

	CameraCalibParam() :
		leng(0.0), cell(0.0), F(0.0), calibration_flags(0) {}

	void setF() {
		if (leng == 0.0 || cell == 0.0) F = 0.0;
		else {
			F = leng / cell;
		}
	}

	/// �p�����[�^��������l���Z�b�g����. �L�[�̖��O�̓����o�ϐ��Ɠ���(�����Acalibration_flags�����͂�����ƈႤ)
	void set(std::map<std::string, double> &params) {
		// �t���O�l�쐬
		int cflags = 0;
		if (params.count("CV_CALIB_USE_INTRINSIC_GUESS") && params["CV_CALIB_USE_INTRINSIC_GUESS"] == 1.0)
			cflags += cv::CALIB_USE_INTRINSIC_GUESS;
		if (params.count("CV_CALIB_FIX_PRINCIPAL_POINT") && params["CV_CALIB_FIX_PRINCIPAL_POINT"] == 1.0)
			cflags += cv::CALIB_FIX_PRINCIPAL_POINT;
		if (params.count("CV_CALIB_FIX_ASPECT_RATIO") && params["CV_CALIB_FIX_ASPECT_RATIO"] == 1.0)
			cflags += cv::CALIB_FIX_ASPECT_RATIO;
		if (params.count("CV_CALIB_ZERO_TANGENT_DIST") && params["CV_CALIB_ZERO_TANGENT_DIST"] == 1.0)
			cflags += cv::CALIB_ZERO_TANGENT_DIST;
		if (params.count("CV_CALIB_FIX_K1") && params["CV_CALIB_FIX_K1"] == 1.0)
			cflags += cv::CALIB_FIX_K1;
		if (params.count("CV_CALIB_FIX_K2") && params["CV_CALIB_FIX_K2"] == 1.0)
			cflags += cv::CALIB_FIX_K2;
		if (params.count("CV_CALIB_FIX_K3") && params["CV_CALIB_FIX_K3"] == 1.0)
			cflags += cv::CALIB_FIX_K3;
		if (params.count("CV_CALIB_FIX_K4") && params["CV_CALIB_FIX_K4"] == 1.0)
			cflags += cv::CALIB_FIX_K4;
		if (params.count("CV_CALIB_FIX_K5") && params["CV_CALIB_FIX_K5"] == 1.0)
			cflags += cv::CALIB_FIX_K5;
		if (params.count("CV_CALIB_FIX_K6") && params["CV_CALIB_FIX_K6"] == 1.0)
			cflags += cv::CALIB_FIX_K6;
		if (params.count("CV_CALIB_RATIONAL_MODEL") && params["CV_CALIB_RATIONAL_MODEL"] == 1.0)
			cflags += cv::CALIB_RATIONAL_MODEL;
		this->calibration_flags = cflags;

		if (params.count("cell")) this->cell = params["cell"];
		if (params.count("leng")) this->leng = params["leng"];
		this->setF();
	}
};


class iCameraCalibrator {
public:
	virtual ~iCameraCalibrator() {}
	
	/**
	 * �f�X�g���N�^�Ăяo��
	 */
	virtual void destroy() = 0;

	/**
	 * �p�����[�^��ݒ肵�܂�.
	 * @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] prcp �}�[�J���o�̂��߂̑O�����p�p�����[�^
	 * @param [in] mrkp �~�}�[�J���o�̂��߂̃p�����[�^
	 * @param [in] brdp �L�����u�{�[�h�̃p�����[�^
	 */
	virtual bool set_parameters(PreProcParam &prcp, CircleMarkerParam &mrkp, CalibBoardParam &brdp) = 0;

	/**
	 * �L�����u���[�V�����^�[�Q�b�g�摜���ꖇ�ǉ����܂�.
	 * @return 0������. -1���}�[�J���o�킪�쐬����Ă��Ȃ�. ���̑��̓}�[�J���o��Ԓl.
	 * @param [in] image �摜����[�A�h���X
	 * @param [in] width �摜����
	 * @param [in] height �摜�c��
	 * @param [in] step �摜�o�b�t�@�̐��������̃o�C�g��
	 * @param [in] show_result �}�[�J���o���ʉ摜����ʂɕ\������(true)����(false)��
	 * @param [in] filename �}�[�J���o���ʉ摜�ۑ���t�@�C����(string()��^�����ꍇ�͕ۑ����Ȃ�)
	 */
	virtual int put_image(unsigned char *image, const int width, const int height, const size_t step, const bool show_result = true, const std::string filename = std::string()) = 0;

	/**
	 * �L�����u���[�V�����^�[�Q�b�g�摜���t�@�C������ǂݍ���ňꖇ�ǉ����܂�.
	 * @return 0������. -1���}�[�J���o�킪�쐬����Ă��Ȃ�. -2���摜���ǂݍ��߂Ȃ�. ���̑��̓}�[�J���o��Ԓl.
	 * @param [in] i_filename ���͉摜�t�@�C����
	 * @param [in] show_result �}�[�J���o���ʉ摜����ʂɕ\������(true)����(false)��
	 * @param [in] o_filename �}�[�J���o���ʉ摜�ۑ���t�@�C����(string()��^�����ꍇ�͕ۑ����Ȃ�)
	 * @warning �A���摜�ɂ͖��Ή��ł�.
	 */
	virtual int put_image(const std::string i_filename, const bool show_result = true, const std::string o_filename = std::string()) = 0;

	/**
	 * �L�����u���[�V���������s���܂�.
	 * @return �L�����u���[�V�����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] camp �L�����u���[�V�����p�����[�^
	 * @param [out] reprojerr �ē��e�덷
	 * @param [out] camerr �J�����덷
	 */
	virtual bool do_calibrate(CameraCalibParam &camp, std::vector<double>* reprojerr = 0, double *camerr = 0) = 0;

	/**
	 * �L�����u���[�V�������ʂ��t�@�C���ɕۑ����܂�.
	 * @return �ۑ��ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] filename �ۑ���t�@�C����.
	 * @param [in] cam_name �J������(�p�����[�^�t�@�C����ǂݍ���ŃJ�������쐬����Ƃ��ɁA�����J�������łȂ��Ɛ������ǂݍ��߂܂���.)
	 * @warning �t�@�C�����̊g���q��".xml"�Ƃ����XML�`���ŁA".yaml"�Ƃ����YAML�`���ŕۑ�����܂�.
	 */
	virtual bool save_calibfile(const std::string filename, const std::string cam_name = std::string()) = 0;
};


/// ���N�e�B�t�@�C�p�����[�^�^
struct RectifyParam {
	double alpha;	///< �X�P�[�����O�p�����[�^
	int flags;		///< ���N�e�B�t�@�C�t���O
	int new_width;	///< ���N�e�B�t�@�C��̉摜����
	int new_height;	///< ���N�e�B�t�@�C��̉摜�c��
	int nopL;		///< ���J�����p�w�i��f�l
	int nopR;		///< �E�J�����p�w�i��f�l

	RectifyParam() :
		alpha(-1.0),	///< �X�P�[�����O�p�����[�^.-1�ȊO�̒l�ł����0�`1�̊Ԃ̒l.0���ƗL���Ȕ͈͂̂݉摜�Ɏc��悤�Ɋg�傳��A1���ƌ��̉摜���S�Ď��܂�悤�ɏk�������
		flags(0),		///< �����t���O.��_�����E�ł��炷
		new_width(0),	///< ���N�e�B�t�@�C��̉摜����(0�̏ꍇ�͓��͂Ɠ���)
		new_height(0),	///< ���N�e�B�t�@�C��̉摜�c��(0�̏ꍇ�͓��͂Ɠ���)
		nopL(0),		///< ���摜�̖����ȉ�f�ɑ΂��ė^������l(0�`255)
		nopR(0) 		///< �E�摜�̖����ȉ�f�ɑ΂��ė^������l(0�`255)
	{}

	/// �p�����[�^��������l���Z�b�g����. �L�[�̖��O�̓����o�ϐ��Ɠ���
	void set(std::map<std::string, double> &params) {
		if (params.count("alpha")) this->alpha = params["alpha"];
		if (params.count("flags")) this->flags = (params["flags"] == 0.0) ? 0 : cv::CALIB_ZERO_DISPARITY;
		if (params.count("new_width")) this->new_width = (params["new_width"] <= 0) ? 0 : (int)params["new_width"];
		if (params.count("new_height")) this->new_height = (params["new_height"] <= 0) ? 0 : (int)params["new_height"];
		if (params.count("nopL")) this->nopL = (params["nopL"] <= 0) ? 0 : ((params["nopL"] >= 255) ? 255 : (int)params["nopL"]);
		if (params.count("nopR")) this->nopL = (params["nopR"] <= 0) ? 0 : ((params["nopR"] >= 255) ? 255 : (int)params["nopR"]);
	}
};


class iStereoCalibrator {
public:
	virtual ~iStereoCalibrator() {}
	
	/**
	 * �f�X�g���N�^�Ăяo��
	 */
	virtual void destroy() = 0;

	/**
	 * �p�����[�^��ݒ肵�܂�.
	 * @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] prcp �}�[�J���o�̂��߂̑O�����p�p�����[�^
	 * @param [in] mrkp �~�}�[�J���o�̂��߂̃p�����[�^
	 * @param [in] brdp �L�����u�{�[�h�̃p�����[�^
	 */
	virtual bool set_parameters(PreProcParam &prcp, CircleMarkerParam &mrkp, CalibBoardParam &brdp) = 0;

	/**
	 * �L�����u���[�V�����^�[�Q�b�g�摜���ꖇ�ǉ����܂�.
	 * @return 0������.-1���}�[�J���o�킪�쐬����Ă��Ȃ�. -2���J�����ԍ����s��. ���̑��̓}�[�J���o��Ԓl.
	 * @param [in] cid �J�����ԍ�
	 * @param [in] image �摜����[�A�h���X
	 * @param [in] width �摜����
	 * @param [in] height �摜�c��
	 * @param [in] step �摜�o�b�t�@�̐��������̃o�C�g��
	 * @param [in] show_result �}�[�J���o���ʉ摜����ʂɕ\������(true)����(false)��
	 * @param [in] filename �}�[�J���o���ʉ摜�ۑ���t�@�C����(string()��^�����ꍇ�͕ۑ����Ȃ�)
	 * @warning �ǉ������摜�͍��E�ŏ��Ԃ�ς��Ȃ��ł�������. (���J����n�Ԗڂ̉摜�ƉE�J����n�Ԗڂ̉摜�͕K�������V�[����
	 * ���E�J�����ŎB�e�������̂Ƃ��Ă�������).
	 */
	virtual int put_image(const int cid, unsigned char *image, const int width, const int height, const size_t step, const bool show_result = true, const std::string filename = std::string()) = 0;

	/**
	 * �L�����u���[�V�����^�[�Q�b�g�摜���t�@�C������ǂݍ���ňꖇ�ǉ����܂�.
	 * @return 0������.-1���}�[�J���o�킪�쐬����Ă��Ȃ�. -2���J�����ԍ����s��. -3���摜���ǂݍ��߂Ȃ�. ���̑��̓}�[�J���o��Ԓl.
	 * @param [in] cid �J�����ԍ�
	 * @param [in] i_filename ���͉摜�t�@�C����
	 * @param [in] show_result �}�[�J���o���ʉ摜����ʂɕ\������(true)����(false)��
	 * @param [in] o_filename �}�[�J���o���ʉ摜�ۑ���t�@�C����(string()��^�����ꍇ�͕ۑ����Ȃ�)
	 * @warning �ǉ������摜�͍��E�ŏ��Ԃ�ς��Ȃ��ł�������. (���J����n�Ԗڂ̉摜�ƉE�J����n�Ԗڂ̉摜�͕K�������V�[����
	 * ���E�J�����ŎB�e�������̂Ƃ��Ă�������).
	 * @warning �����摜�p�ł�.
	 */
	virtual int put_image(const int cid, const std::string i_filename, const bool show_result = true, const std::string filename = std::string()) = 0;

	/**
	 * �L�����u���[�V�����^�[�Q�b�g�摜(���E�A���摜)���t�@�C������ǂݍ���Œǉ����܂�.
	 * @return 0������.-1���}�[�J���o�킪�쐬����Ă��Ȃ�. -2���摜���ǂݍ��߂Ȃ�. ���̑��̓}�[�J���o��Ԓl(��4bit���J����, ��4bit�E�J����).
	 * @param [in] i_filename ���͉摜�t�@�C����
	 * @param [in] show_result �}�[�J���o���ʉ摜����ʂɕ\������(true)����(false)��
	 * @param [in] o_filename �}�[�J���o���ʉ摜�ۑ���t�@�C����(string()��^�����ꍇ�͕ۑ����Ȃ�)
	 * @warning �A���摜(���A��)�摜�p�ł�.
	 */
	virtual int put_image(const std::string i_filename, const bool show_result = true, const std::string filename = std::string()) = 0;

	/**
	 * �L�����u���[�V���������s���܂�.
	 * @return �L�����u���[�V�����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] camp �L�����u���[�V�����p�����[�^
	 * @param [out] reprojerr �ē��e�덷
	 * @param [out] camerr �J�����덷
	 */
	virtual bool do_calibrate(CameraCalibParam &camp, std::vector<std::vector<double>>* reprojerr = 0, double *camerr = 0) = 0;

	/**
	 * �L�����u���[�V��������(�c�ݗL�J�����̃J�����p�����[�^)���t�@�C���ɕۑ����܂�.
	 * @return �ۑ��ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] cam0_filename ��J����(���J����)�̃p�����[�^�ۑ���t�@�C����.
	 * @param [in] cam1_filename �⏕�J����(�E�J����)�̃p�����[�^�ۑ���t�@�C����.
	 * @warning �t�@�C�����̊g���q��".xml"�Ƃ����XML�`���ŁA".yaml"�Ƃ����YAML�`���ŕۑ�����܂�.
	 */
	virtual bool save_calibfile(const std::string cam0_filename, const std::string cam1_filename) = 0;

	/**
	 * ���N�e�B�t�@�C�����s���A�X�e���I�J�������쐬���܂�.
	 * @return �쐬�ɐ��������ꍇ�͊�������A���s�����ꍇ��-1���Ԃ�܂�.
	 * @param [in] rp ���N�e�B�t�@�C�p�����[�^
	 * @param [out] roiL ���J�����̌��摜�ɂ�����L���͈�(x, y, w, h)���i�[����z��(4����int���K�v)
	 * @param [out] roiR �E�J�����̌��摜�ɂ�����L���͈�(x, y, w, h)���i�[����z��(4����int���K�v)
	 */
	virtual double create_stereo_camera(RectifyParam &rp, int *roiL = 0, int *roiR = 0) = 0;		

	/**
	 * �{�[�h���W�n�ւ̕ϊ��s����쐬���܂�.
	 * @return ���������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] imageL ���J�����Q�Ɖ摜
	 * @param [in] imageR �E�J�����Q�Ɖ摜
	 */
	virtual bool create_stereo_brdcrd(unsigned char *imageL, const size_t stepL, unsigned char *imageR, const size_t stepR) = 0;

	/**
	 * �{�[�h���W�n�ւ̕ϊ��s����쐬���܂�.
	 * @return ���������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] filenameL ���J�����Q�Ɖ摜�t�@�C����
	 * @param [in] filenameR �E�J�����Q�Ɖ摜�t�@�C����
	 * @warning �����摜�p�ł�.
	 */
	virtual bool create_stereo_brdcrd(const std::string filenameL, const std::string filenameR) = 0;

	/**
	 * �{�[�h���W�n�ւ̕ϊ��s����쐬���܂�.
	 * @return ���������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] filename ���E�J�����Q�Ɖ摜�t�@�C����
	 * @warning �A���摜�p�ł�.
	 */
	virtual bool create_stereo_brdcrd(const std::string filename) = 0;

	/**
	 * �쐬���ꂽ�X�e���I�J�����p�����[�^���t�@�C���ɕۑ����܂�.
	 * @return �ۑ��ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] filename �X�e���I�J�����p�����[�^�ۑ���t�@�C����
	 * @param [in] lname ���J�����̃��N�e�B�t�@�C�}�b�v�ۑ���t�@�C����
	 * @param [in] rname �E�J�����̃��N�e�B�t�@�C�}�b�v�ۑ���t�@�C����
	 * @warning �t�@�C�����̊g���q��".xml"�Ƃ����XML�`���ŁA".yaml"�Ƃ����YAML�`���ŕۑ�����܂�.
	 * @warning lname, rname���w�肵�Ȃ��ꍇ�A���N�e�B�t�@�C�}�b�v�͕ۑ�����܂���.
	 */
	virtual bool save_stereofile(const std::string filename, 
		const std::string lname = std::string(), const std::string rname = std::string()) = 0;

	/**
	 * HMat�`���ŃX�e���I�J�����p�����[�^���t�@�C���ɕۑ����܂�.
	 * @return �ۑ��ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] hmat0_name ���J����PPM(Hmat)�p�̃t�@�C����
	 * @param [in] hmat1_name �E�J����PPM(Hmat)�p�̃t�@�C����
	 * @param [in] rectmap_name ���N�e�B�t�@�C�e�[�u���p�̃t�@�C����
	 * @param [in] isbrd �{�[�h���W�n�ɕϊ����Ă���o�͂��邩�ۂ�
	 */
	virtual bool save_stereohmat(const std::string hmat0_name, const std::string hmat1_name, const std::string rectmap_name, const bool isbrd = false) = 0;

	/**
	 * �{�[�h���W�n�ւ̕ϊ��s����t�@�C���ɕۑ����܂�.
	 * @return �ۑ��ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] filename �ۑ���t�@�C����
	 */
	virtual bool save_boardRT(const std::string filename) = 0;
};

#ifdef _WINDOWS
#ifdef _WINDLL
#define EXPORT_CALIB __declspec(dllexport)
#else
#define EXPORT_CALIB __declspec(dllimport)
#endif
#else
#define EXPORT_CALIB
#endif


/**
 * �P�̃J�����L�����u���[�V�����N���X�C���X�^���X�쐬�֐�
 * @return �N���X�C���X�^���X�̃A�h���X
 */
extern "C" EXPORT_CALIB iCameraCalibrator* CreateCameraCalibrator();
typedef iCameraCalibrator *(*pCreateCameraCalibrator)();

/**
 * �X�e���I�J�����L�����u���[�V�����N���X�C���X�^���X�쐬�֐�
 * @return �N���X�C���X�^���X�̃A�h���X
 */
extern "C" EXPORT_CALIB iStereoCalibrator* CreateStereoCalibrator();
typedef iStereoCalibrator *(*pCreateStereoCalibrator)();
