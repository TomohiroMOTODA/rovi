/*
 * @file iCalibBoardRecognizer.hpp
 * @breif �L�����u�{�[�h�F����̃C���^�[�t�F�[�X 
 * @date 2019/09/21
 *
 * @note �L�����u�{�[�h��, �u�Z�}�[�J�v�A�u�O���b�h��Ƀ}�[�J���z�u�v�A�u��}�[�J�͓�d�ہv�̏����𖞂����Ă����
 * ���肵�Ă���. ����ȊO�͍��̂Ƃ���z�肵�Ă��Ȃ�.
 * @note �L�����u�{�[�h�͉����̋�`�ŁA���ӂ̍�������Y���̐��̌����A�Z�ӂ̏������X���̐��̌����Ƃ���B
 * @note ���_�ʒu�͕K����}�[�J�Ƃ��ė^�����Ă��Ȃ���΂Ȃ�Ȃ�.
 */

#pragma once

#ifndef _USE_MATH_DEFINES
#define _USE_MATH_DEFINES
#include <math.h>
#endif	// _USE_MATH_DEFINES

#include <opencv2/opencv.hpp>
#include <map>


/* �K�v�ȃp�����[�^�Ƃ��̃f�t�H���g�l */

 /// �}�[�J���o�̂��߂̑O�����p�p�����[�^
struct PreProcParam {
	bool reverse_bw;		///< �������]���s�����H
	bool equalize_hist;	///< �q�X�g�O�����ψꉻ���s����?
	bool smoothing;		///< �X���[�W���O���s����?
	int bin_type;	///< ��l���^�C�v(0: �ʏ��l��, 1: ���ʕ��͓�l��, 2: �K����l��)
	int bin_param0;	///< ��l��臒l0(bin_type==0�̏ꍇ臒l, bin_type==2�̏ꍇ�u���b�N�T�C�Y, ���̑��̏ꍇ�͎g�p���Ȃ�)
	int bin_param1;	///< ��l��臒l1(bin_type==2�̏ꍇ���ϒl����̃I�t�Z�b�g�l, ���̑��̏ꍇ�͎g���Ȃ�)
	double gamma_correction;	///< gamma�␳�l

	/// �R���X�g���N�^. �f�t�H���g�l��ݒ�
	PreProcParam() :
		reverse_bw(false),
		equalize_hist(false),
		smoothing(false),
		bin_type(1),
		bin_param0(0),
		bin_param1(0),
		gamma_correction(1.0)
	{}

	/// �p�����[�^��������l���Z�b�g����.�L�[�̖��O�̓����o�ϐ��Ɠ���
	void set(std::map<std::string, double> &params) {
		if (params.count("reverse_bw")) this->reverse_bw = (params["reverse_bw"] == 0.0) ? false : true;
		if (params.count("equalize_hist")) this->equalize_hist = (params["equalize_hist"] == 0.0) ? false : true;
		if (params.count("smoothing")) this->smoothing = (params["smoothing"] == 0.0) ? false : true;
		if (params.count("bin_type")) this->bin_type = (int)params["bin_type"];
		if (params.count("bin_param0")) this->bin_param0 = (int)params["bin_param0"];
		if (params.count("bin_param1")) this->bin_param1 = (int)params["bin_param1"];
		if (params.count("gamma_correction")) this->gamma_correction = params["gamma_correction"];
	}
};


/// �~�}�[�J���o�̂��߂̃p�����[�^
struct CircleMarkerParam {
	// �O����w�肵�Ė��Ȃ��ƂȂ�Ȃ����A�ʂɃf�t�H���g�l�ł����Ȃ��Ǝv����p�����[�^
	double fitscore;	///< �֊s������ߎ����ꂽ�ȉ~��ɏ���Ă���֊s���_�̊����̉����l(������Ⴏ��΂��̗֊s���͑ȉ~�ł͂Ȃ��Ɣ��f����)
	int n_circles_minimum;		///< �Œ������ȏ�͌������Ă���Ȃ���΍���}�[�J�̐�
	double max_radius;	///< �ߎ��ȉ~�̒����a�̏���l(�K����ȏ�̒l)
	double min_radius;	///< �ߎ��ȉ~�̒Z���a�̉����l(�K����ȏ�̒l)

	// �O����w�肵�Ė��Ȃ��Ƃǂ����悤���Ȃ��p�����[�^�����ǂȂ��Ă��ǂ�(debug_show_scale!=0�̂Ƃ������K�v)
	int image_width;	///< �摜����
	int image_height;	///< �摜�c��
	double debug_show_scale;	///< �f�o�b�O�摜��\������Ƃ��ɉ��{�ŕ\�����邩(0.0�ɂ��Ă����ƕ\�����Ȃ�)

	/**
	 * �R���X�g���N�^. �f�t�H���g�l��ݒ�
	 */
	CircleMarkerParam() :
		fitscore(0.9),
		n_circles_minimum(9), max_radius(1500), min_radius(8), 
		image_width(0), image_height(0), debug_show_scale(0.0) {}


	/// �p�����[�^��������l���Z�b�g����.�L�[�̖��O�̓����o�ϐ��Ɠ���
	void set(std::map<std::string, double> &params) {
		if (params.count("fitscore")) this->fitscore = params["fitscore"];
		if (params.count("n_circles_minimum")) this->n_circles_minimum = (int)params["n_circles_minimum"];
		if (params.count("max_radius")) this->max_radius = params["max_radius"];
		if (params.count("min_radius")) this->min_radius = params["min_radius"];
		if (params.count("debug_show_scale")) this->debug_show_scale = params["debug_show_scale"];
	}
};

/// �L�����u�{�[�h�̃p�����[�^
struct CalibBoardParam {
	double unitleng;	///< �~�}�[�J�d�S�ԋ���
	int n_circles_x;	///< X�������̃}�[�J��
	int n_circles_y;	///< Y�������̃}�[�J��
	int origin_x;	///< X���́{�������猴�_�܂ł̃}�[�J��(0�X�^�[�g�Ő�����)
	int origin_y;	///< Y���́{�������猴�_�܂ł̃}�[�J��(0�X�^�[�g�Ő�����)
	double distance_between_circles;	///< �d�S�ԋ����̉~�̒��a�ɑ΂���䗦(�����_���ʂ܂ŗL��)

	// �R���X�g���N�^. �f�t�H���g�l��ݒ�
	CalibBoardParam() :
		unitleng(0.0), n_circles_x(0), n_circles_y(0), origin_x(0), origin_y(0),
		distance_between_circles(1.2)
	{}

	/// �p�����[�^��������l���Z�b�g����.�L�[�̖��O�̓����o�ϐ��Ɠ���
	bool set(std::map<std::string, double> &params) {
		if (params.count("unitleng")) this->unitleng = params["unitleng"];
		if (params.count("n_circles_x")) this->n_circles_x = (int)params["n_circles_x"];
		if (params.count("n_circles_y")) this->n_circles_y = (int)params["n_circles_y"];
		if (params.count("origin_x")) this->origin_x = (int)params["origin_x"];
		if (params.count("origin_y")) this->origin_y = (int)params["origin_y"];
		if (params.count("distance_between_circles")) this->distance_between_circles = params["distance_between_circles"];

		if (unitleng == 0.0 || n_circles_x == 0 || n_circles_y == 0 ||
			distance_between_circles == 0.0) return false;
		else return true;
	}
};



/// �L�����u�{�[�h�F����̃C���^�[�t�F�[�X
class iCalibBoardRecognizer {
public:
	virtual void destroy() = 0;
	virtual ~iCalibBoardRecognizer() {}

	/**
	 * �p�����[�^��ݒ肵�܂�.
	 * @return �p�����[�^�ݒ�ɖ�肪�����false, �������true.
	 * @param [in] pp �}�[�J���o�̂��߂̑O�����p�p�����[�^
	 * @param [in] mp �~�}�[�J���o�̂��߂̃p�����[�^
	 * @param [in] cp �L�����u�{�[�h�̃p�����[�^
	 */
	virtual bool set_parameters(PreProcParam &pp, CircleMarkerParam &mp, CalibBoardParam &cp) = 0;

	/**
	 * �}�[�J�̈ʒu�֌W�����ʂ��܂�.
	 * @return ��Ԓl(���������ꍇ�̓[��, ���s�����ꍇ�͔�[���̃G���[�ԍ�)
	 * @param [in] image �����Ώۉ摜
	 * @param [out] point2d �}�[�J�̉摜�����W�l���i�[����Ă�o�b�t�@
	 */
	virtual int recognize(cv::Mat &image, std::vector<cv::Point2f> &point2d) = 0;

	/**
	 * ��L�̏�Ԓl�̃G���[���b�Z�[�W�̖��O��Ԃ��܂�.
	 * @return �G���[���b�Z�[�W
	 * @param [in] status ��Ԓl
	 */
	virtual std::string get_error_name(const int status = -1) = 0;

	/**
	 * �����Ώۉ摜�̉摜�T�C�Y��Ԃ��܂�.
	 * @return �����Ώۉ摜�̉摜�T�C�Y
	 * @warning �A���A�ꖇ�ł��}�[�J���o���s������łȂ���ΗL���ɂȂ�Ȃ�
	 */
	virtual cv::Size image_size() = 0;

	/**
	 * �}�[�J���W�͈̔͂�Ԃ��܂�
	 * @return �}�[�J���W�͈̔�(cv::Rect(X�������̍ŏ��l�AY�������̍ŏ��l, X�͈̔�, Y�͈̔�)
	 */
	virtual const cv::Rect get_marker_range() const = 0;

	/**
	 * �}�[�J�̏c���̈ʒu����A���̍��W�l���i�[����Ă���o�b�t�@�ɂ�����C���f�b�N�X��Ԃ��܂�.
	 * @return �C���f�b�N�X�l
	 * @param [in] pos �}�[�J��(x,y)�ʒu
	 */
	virtual const int get_marker_index(cv::Point pos) const = 0;

	/**
	 * �摜��ł̃}�[�J�ʒu���擾�o���Ă���_���������o���āAimgPoints�ɕۑ�����B���������ɂȂ�悤
	 * ��objPoints�ɂ��̎O�����ʒu���i�[����.
	 * @return �ʒu���擾���ꂽ�}�[�J��
	 * @param [in] point2d �}�[�J�ʒu
	 * @param [out] imgPoints ��L�̃}�[�J�ʒu�̓��A�ǂݎ�ꂽ�ʒu�̂ݎ��o��������
	 * @param [out] objPoints imgPoints[i]�ɑΉ�����O�����ʒu
	 */
	virtual size_t corresponding_points(const std::vector<cv::Point2f> &point2d,
		std::vector<cv::Point2f> &imgPoints,
		std::vector<cv::Point3f> &objPoints) = 0;

	/**
	 * ���E�摜��ł̃}�[�J�ʒu���擾�o���Ă���_���������o���āAimgPointsL, imgPointsR�ɕۑ�����B
	 * ���������ɂȂ�悤�ɁApobjPoints�ɂ��̎O�����ʒu���i�[����.
	 * @return �ʒu���擾���ꂽ�}�[�J��
	 * @param [in] point2dL ���J�����̃}�[�J�ʒu
	 * @param [in] point2dR �E�J�����̃}�[�J�ʒu
	 * @param [out] imgPointsL ���J�����}�[�J�ʒu�̓��A�ǂݎ�ꂽ�ʒu�̂ݎ��o��������
	 * @param [out] imgPointsR �E�J�����}�[�J�ʒu�̓��A�ǂݎ�ꂽ�ʒu�̂ݎ��o��������
	 * @param [out] objPoints imgPoints*[i]�ɑΉ�����O�����ʒu
	 */
	virtual size_t corresponding_points(const std::vector<cv::Point2f> &point2dL, const std::vector<cv::Point2f> &point2dR,
		std::vector<cv::Point2f> &imgPointsL,
		std::vector<cv::Point2f> &imgPointsR,
		std::vector<cv::Point3f> &objPoints) = 0;

	/**
	 * �}�[�J���ʌ��ʉ摜���t�@�C���ɕۑ����܂�.
	 * @return �Ȃ�
	 * @parma [in] filename �ۑ���t�@�C����
	 * @param [in] ret iCalibBoardRecognizer::recognize()�̖߂�l
	 */
	virtual void save_result_image(std::string filename, const int ret = -1) = 0;


	/**
	 * �}�[�J���ʌ��ʉ摜���R�s�[���܂�.
	 * @return �Ȃ�
	 * @param [in] image �R�s�[��摜
	 * @param [in] ret iCalibBoardRecognizer::recognize()�̖߂�l
	 */
	virtual void copy_result_image(cv::Mat &image, const int ret = -1) = 0;
	
	/**
	 * �}�[�J���ʌ��ʉ摜����ʂɕ\�����܂�.
	 * @return �Ȃ�
	 * @param [in] ret iCalibBoardRecognizer::recognize()�̖߂�l
	 */
	virtual void show_result_image(const int ret = -1) = 0;
};

#ifdef _WINDOWS
#ifdef _WINDLL
#define EXPORT_BOARD __declspec(dllexport)
#else
#define EXPORT_BOARD __declspec(dllimport)
#endif
#else
#define EXPORT_BOARD
#endif


/**
 * �L�����u���[�V�����{�[�h�F����N���X�C���X�^���X�쐬
 * @return �N���X�C���X�^���X�̃A�h���X
 */
extern "C" EXPORT_BOARD iCalibBoardRecognizer* CreateCalibBoardRecognizer();

typedef iCalibBoardRecognizer *(*pCreateCalibBoardRecognizer)();
