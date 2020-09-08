#pragma once

#include "iCalibBoardRecognizer.hpp"
#include <string>


/**
 * �L�����u���[�V�����{�[�h�p�������C���^�[�t�F�[�X
 */
class iCalibBoardPoseSolver {
public:
	/**
	 * �f�X�g���N�^�Ăяo��
	 */
	virtual void destroy() = 0;

	/**
	 * �J�����̏��������s���܂�.
	 * @return �������ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] filenames �t�@�C�����╶���񂪊i�[���ꂽ���X�g.�K�v�ȍ��ڂ�camera_type�ɂ���ĈقȂ�B
	 * @param [in] camera_type �J�����^�C�v.�ȉ��̒ʂ�.
	 * - 0: �c�ݗL�J����. filenames[0]�ɂ͘c�ݗL�J�����̃J�����p�����[�^�t�@�C�������i�[���邱��.
	 *
	 * - 1: �X�e���I���J����. ��̘c�ݗL�J��������X�e���I���s���J�������쐬���A���̍��J�������p������
	 *		�Ɏg�p����.filenames[0]�ɂ͍����c�ݗL�J�����̃J�����p�����[�^�t�@�C��(cam0_param.yaml��)���A
	 *		filenames[1]�ɂ͉E���c�ݗL�J�����̃J�����p�����[�^�t�@�C��(cam1_param.yaml��)���w�肷�邱��.
	 *
	 * - 2: StereoParam�c�ݕ␳�J����. filenames[0]�ɂ̓X�e���I�p�����[�^�t�@�C�����Afilenames[1]�ɂ�
	 *		���J�����̕��s���}�b�v�t�@�C�������i�[���邱��(�E�͂����Ă��g��Ȃ��̂ŗv��Ȃ�).
	 *
	 * - 3: Hmat�`���X�e���I�c�ݕ␳�J����. filenames[0]�ɂ͍��J������Hmat�Afilenames[1]�ɂ͉E�J������Hmat�A
	 *		filenames[2]�ɂ͕��s���}�b�v�̃t�@�C�������i�[���邱��. �܂��A���̃J�����̏ꍇ�A���͉摜�̃T�C�Y��
	 *		�K�v�ɂȂ�̂ŕK��, image_width, image_height���w�肷�邱��.
	 *
	 * - 4: �s���z�[���J����. filenames[0]�ɂ̓s���z�[���J�����̃J�����p�����[�^�t�@�C�����w�肷�邱��.����
	 *		�ꍇ�͓��͉摜�́A�s���z�[���J�����ŎB�e�����l�ɕϊ�����Ă��Ȃ���΂Ȃ�Ȃ�.
	 */
	virtual bool init_camera(const std::vector<std::string> &filenames, const int camera_type = 0,
		const int image_width = 0, const int image_height = 0) = 0;

	/**
	 * �L�����u���[�V�����{�[�h�̃p�����[�^�ݒ���s���܂�.
	 * @return �p�����[�^����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param [in] pp �}�[�J���o�̂��߂̑O�����p�p�����[�^
	 * @param [in] mp �~�}�[�J���o�̂��߂̃p�����[�^
	 * @param [in] cp �L�����u�{�[�h�̃p�����[�^
	 */
	virtual bool set_parameters(PreProcParam &pp, CircleMarkerParam &mp, CalibBoardParam &cp) = 0;


	// �{�[�h�̎p������ ------------------------------------------------------

	/**
	 * �^����ꂽ�L�����u�{�[�h�摜����{�[�h�̎p���𐄒肵�܂�.
	 * @return ���肳�ꂽ�p�����g���ē���ꂽ�}�[�J�_�̍ē��e�덷(���ϒl). �p������Ɏ��s�����畉�̒l
	 * @param[in] image  ���͉摜����[�A�h���X
	 * @param[in] width  �摜����
	 * @param[in] height �摜�c��
	 * @param[in] step   �摜�o�b�t�@�̐��������̃o�C�g��
	 * @param [out] pose ���肳�ꂽ�{�[�h�̎p��(�O3�v�f�ړ��x�N�g���A��R�v�f��]�x�N�g��)
	 */
	virtual double solve_pose(unsigned char *image, const int width, const int height, const size_t step,
		double *pose = 0) = 0;

	/**
	 * �^����ꂽ�t�@�C��������摜��ǂݍ��݁A�{�[�h�̎p���𐄒肵�܂�.
	 * @return ���肳�ꂽ�p�����g���ē���ꂽ�}�[�J�_�̍ē��e�덷(���ϒl). �p������Ɏ��s�����畉�̒l
	 * @param [in] imagename �摜�t�@�C����
	 * @param [in] is_connected �A���摜�̏ꍇ��true, �����łȂ����false.(�A���摜�̏ꍇ�͍����̂ݎg�p���܂�)
	 * @param [out] pose ���肳�ꂽ�{�[�h�̎p��(�O3�v�f�ړ��x�N�g���A��R�v�f��]�x�N�g��)
	 */
	virtual double solve_pose(const std::string filename, const bool is_connected = false, double *pose = 0) = 0;

	// �o�� ----------------------------------------------------------------

	/**
	 * ���o���ꂽ�}�[�J��`�悵���摜���w�肳�ꂽ�t�@�C�����ŕۑ����܂�.
	 * @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 * @param filename �摜�t�@�C����
	 */
	virtual bool save_debug_image(const std::string filename) = 0;

	/**
	 * ��ʂɃ}�[�J���o���ʂ�\�����܂�.
	 * @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	 */
	virtual bool show_debug_image() = 0;

	/**
	 * �}�[�J���o���ʉ摜(RGB�J���[)�o�b�t�@�̐擪�A�h���X��Ԃ��܂�.
	 * @return �o�b�t�@�擪�A�h���X
	 */
	virtual unsigned char* ptr_debug_image() = 0;

	/**
	 * �}�[�J���o���ʉ摜�̃T�C�Y�����߂܂�.
	 * @return �Ȃ�
	 * @param [out] width ���ʉ摜�̉���
	 * @param [out] height ���ʉ摜�̏c��
	 * @warning  ���N�e�B�t�@�C�����s���ꂽ�ꍇ�A���͉摜�ƃ}�[�J���o�Ώۉ摜�̃T�C�Y���قȂ邱�Ƃ�����܂�.
	 */
	virtual void get_size(int *width, int *height) = 0;
};


#ifdef _WINDOWS
#ifdef _WINDLL
#define EXPORT_CBSOLVER __declspec(dllexport)
#else
#define EXPORT_CBSOLVER __declspec(dllimport)
#endif
#else
#define EXPORT_CBSOLVER
#endif

/**
 * �n���h�A�C�L�����u���[�V�����N���X�C���X�^���X�쐬�֐�
 * @return �N���X�C���X�^���X�̃A�h���X
 */
extern "C" EXPORT_CBSOLVER iCalibBoardPoseSolver* CreateCalibBoardPoseSolver();

typedef iCalibBoardPoseSolver *(*pCreateCalibBoardPoseSolver)();

