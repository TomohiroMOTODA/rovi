#pragma once
#include <vector>
#include <string>


class iStereoCamera {
public:
	enum { LCAM = 0, RCAM = 1, N_CAMERA = 2 };

	virtual void destroy() = 0;

	/**
	 * �������Ԃ��܂�
	 * @return �����
	 */
	virtual const double get_baseline_length(void) const = 0;

	/**
	 * �X�e���I�J�����̓��͉摜�̃T�C�Y���擾���܂�.
	 * @return �Ȃ�
	 * @param [out] wd ���͉摜�̉������i�[����ϐ��ւ̃|�C���^
	 * @param [out] ht ���͉摜�̏c�����i�[����ϐ��ւ̃|�C���^ 
	 * @note remap�ŗ^������͉摜�̑傫���͕K�������œ���ꂽ�T�C�Y�Ƃ��Ă�������.
	 */
	virtual void get_inpimage_size(int *wd, int *ht) const = 0;

	/**
	 * �X�e���I�J�����̏o�͉摜�̃T�C�Y���擾���܂�.
	 * @return �Ȃ�
	 * @param [out] wd �o�͉摜�̉������i�[����ϐ��ւ̃|�C���^
	 * @param [out] ht �o�͉摜�̏c�����i�[����ϐ��ւ̃|�C���^
	 * @note remap�ŗ^����o�͉摜�̑傫���͕K�������œ���ꂽ�T�C�Y�Ƃ��Ă�������.
	 */
	virtual void get_outimage_size(int *wd, int *ht) const = 0;

	/**
	 * �^����ꂽ���͉摜���X�e���I�J�����̉摜�ɕϊ�(���N�e�B�t�@�C)���܂�.
	 * @return �ϊ��ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [out] o_image �o�͉摜����[�_�̃A�h���X
	 * @param [in] o_step �o�͉摜�o�b�t�@�̐��������̃o�C�g��
	 * @param [in] i_image ���͉摜����[�_�̃A�h���X
	 * @param [in] i_step ���͉摜�o�b�t�@�̐��������̃o�C�g��
	 * @param [in] cam ���J�����̏ꍇ��0, �E�J�����̏ꍇ��1��^����.���͉摜�����E�A���ł���ꍇ��2��^����B
	 * @note cam==2�Ƃ���ꍇ�͕K��o_image�͏o�͉摜�T�C�Y�~2�̃��������m�ۂ��Ă�������.
	 */
	virtual bool remap(unsigned char *o_image, const size_t o_step,
		unsigned char *i_image, const size_t i_step, const int cam) = 0;

	/**
	 * ��������O�����ʒu���v�Z���܂�.
	 * @return �Ȃ�.
	 * @param [out] p �v�Z���ꂽ�O�����ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��3��. x, y, z�p)
	 * @param [in] x, y ���J�����̉�f�̍��W�l
	 * @param [in] disparity ����(���J������X���W�l - �E�J������X���W�l)
	 * @note x, y, disparity�̓��N�e�B�t�@�C�摜�œ���ꂽ�l��^���Ă�������.
	 */
	virtual bool get3dposition(double *p, const int x, const int y, const double disparity) = 0;

	/**
	 * ���E�̓������e�ϊ��s��(P�s��)����ŏ����@�ɂ���ĎO�����ʒu���v�Z���܂�.
	 * @return �Ȃ�.
	 * @param [out] p �v�Z���ꂽ�O�����ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��3��. x, y, z�p)
	 * @param [in] pL ���J�����̉�f�ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��2��. i, j�p)
	 * @param [in] pR �E�J�����̉�f�ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��2��. i, j�p)
	 * @note pL, pR �̓��N�e�B�t�@�C�摜�œ���ꂽ�l��^���Ă�������.
	 */
	virtual bool get3dposition(double *p, const double *pL, const double *pR) = 0;

	/**
	 * ���E�̉�f�ʒu���王���x�N�g�����g�p���ĎO�����ʒu���v�Z���܂�.
	 * @return �O�����ʒu
	 * @param [out] p �v�Z���ꂽ�O�����ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��3��. x, y, z�p)
	 * @param [in] ethr �v�Z�덷�̏���l
	 * @param [in] p0 ���J�����̉�f�ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��2��. i, j�p)
	 * @param [in] p1 �E�J�����̉�f�ʒu���i�[����o�b�t�@�ւ̃|�C���^(�v�f��2��. i, j�p)
	 * @note pL, pR �̓��N�e�B�t�@�C�摜�œ���ꂽ�l��^���Ă�������.
	 */
	virtual bool get3dposition(double *p, const double ethr, const double *pL, const double *pR) = 0;
};


/// �X�e���I�J�����쐬�̂��߂̐ݒ�
struct StereoCameraSettings {
	int input_cols;		///< ����(�J����)�摜�̉���
	int input_rows;		///< ����(�J����)�摜�̏c��

	int output_cols;	///< �o�͉摜�̉���
	int output_rows;	///< �o�͉摜�̏c��

	double alpha;		///< ���N�e�B�t�@�C�̃X�P�[�����O�l
	int flags;			///< ���N�e�B�t�@�C�̃t���O�l

	unsigned char nopL;	///< ���N�e�B�t�@�C��ɍ��J�����摜�̗]���ɑ}�������P�x�l
	unsigned char nopR;	///< ���N�e�B�t�@�C��ɉE�J�����摜�̗]���ɑ}�������P�x�l

	StereoCameraSettings() : alpha(-1.0), flags(0), nopL(0), nopR(0) {}
};



#ifdef _WINDOWS

#ifdef _WINDLL
#define EXPORT_STEREO_CAMERA	__declspec(dllexport)
#else
#define EXPORT_STEREO_CAMERA	__declspec(dllimport)
#endif	// _WINDLL

#else	// else _WINDOWS

#define EXPORT_STEREO_CAMERA

#endif	// _WINDOWS


enum CamParamType {
	HMat = 1,	///< HMat�`���̃X�e���I�J�����t�@�C��s����X�e���I�J�������쐬����
	CamN = 2,	///< cam0_param.yaml, cam1_param.yaml�`���̃J�����p�����[�^�t�@�C������X�e���I�J�������쐬����
};

/**
  �X�e���I�J�������쐬���܂�.
  @return �쐬���ꂽ�X�e���I�J�����̃C���X�^���X
  @param [in] camtype CameraType�̉��ꂩ�̒l
  @param [in] settings �X�e���I�J�����쐬�̂��߂̐ݒ�

  @note CamParamType�ɂ���āA�K�v�ȃt�@�C���̐��Ɩ��O���قȂ�̂Œ���.
  - CamParamType::HMat �̏ꍇ. filenames[0] = ���J�����pHmat, filenames[1] = �E�J�����pHmat, filenames[2] = rect.param
  - CamParamType::CamN �̏ꍇ. filenames[0] = ���J�����̃J�����p�����[�^�t�@�C��, filenames[1] = �E�J�����̃J�����p�����[�^�t�@�C��
 */
extern "C" EXPORT_STEREO_CAMERA iStereoCamera* CreateStereoCamera(const CamParamType camtype,
	const std::vector<std::string> filenames, StereoCameraSettings* settings);

typedef iStereoCamera *(*pCreateStereoCamera)(const int camtype,
	const std::vector<std::string> filenames, StereoCameraSettings* settings);



/**
 * �J�����p�����[�^�f�[�^������ɃR�s�[���܂�.
 * @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
 * @param [in] Kl, Kr ���E�̃J�����p�����[�^(3x3=9�v�f���i�[����Ă���vector<double>)
 * @param [in] Dl, Dr ���E�̘c�݃p�����[�^(0 or 5 or 14 �v�f���i�[����Ă���vector<double>)
 * @param [in] R �E�J����->���J�����̉�]�s��(3x3=9�v�f���i�[����Ă���vector<double>)
 * @param [in] T �E�J����->���J�����̈ړ��x�N�g��(3x1=3�v�f���i�[����Ă���vector<double>)
 * @param [in] settings �X�e���I�J�����쐬�̂��߂̐ݒ�
 */
extern "C" EXPORT_STEREO_CAMERA iStereoCamera* CreateStereoCameraFromRaw(
	std::vector<double> &Kl, std::vector<double> &Kr,
	std::vector<double> &Dl, std::vector<double> &Dr,
	std::vector<double> &R, std::vector<double> &T, StereoCameraSettings* settings);

typedef iStereoCamera *(*pCreateStereoCameraFromRaw)(
	std::vector<double> &Kl, std::vector<double> &Kr,
	std::vector<double> &Dl, std::vector<double> &Dr,
	std::vector<double> &R, std::vector<double> &T, StereoCameraSettings* settings);
