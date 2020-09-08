#pragma once

#include "iStereoCamera.hpp"
#include "iPointCloudGenerator.hpp"
#include <chrono>


class YPCGenerator {
public:
	YPCGenerator()
		: stereo(0), settings(), pcgen(0), method3d(iPointCloudGenerator::Method3D::QMatrix) {
	}

	virtual ~YPCGenerator() {
		if (stereo) stereo->destroy();
		if (pcgen) pcgen->destroy();
	}

	/**
	  �_�Q��������쐬���܂�.
	  @return �쐬�ɐ��������ꍇ��true, ���s�����ꍇ��false
	  @param [in] pcgen_mode �_�Q�������[�h(iPointCloudGenerator.hpp��PcGenMode���Q�Ƃ̎�)
	 */
	virtual bool create_pcgen(const PcGenMode pcgen_mode) = 0;

	/**
	  �_�Q�����p�����[�^�̓ǂݍ��݂��s���A�_�Q������Ƀp�����[�^��n���܂�.
	  @return �ǂݍ��݂ɐ��������ꍇ��true, ���s�����ꍇ��false.
	  @param [in] filename �p�����[�^�t�@�C����
	 */
	virtual bool init(const char *filename) = 0;

	/**
	  �_�Q�����ɕK�v�ȃX�e���I�J�������쐬���܂�.
	  @return �쐬�ɐ��������ꍇ��true, ���s�����ꍇ��false.
	  @param [in] dirname �J�����p�����[�^�t�@�C�����i�[����Ă���f�B���N�g����
	 */
	virtual bool create_camera(const char *dirname) = 0;

	/**
	  �_�Q������ɓn���t�@�C���̃t���p�X�̃��X�g���쐬���܂�.
	  @return �쐬���ꂽ���X�g
	  @param [in] dirname �摜���i�[����Ă���f�B���N�g����
	  @param [in] file_ptn �t�@�C���̊g���q(?)
	  @note ���E�����摜���烊�X�g���쐬����ۂɂ́A�摜����0, �E0, ��1, �E1, ... �̏��ɂȂ�悤���ׂĂ�������.
	  @note �A���摜�͉����тŘA������Ă���摜�̂ݗL���ł�
	 */
	virtual std::vector<std::string> create_filelist(const char *dirname, const char *file_ptn) = 0;

	/**
	  �o�ߎ��Ԃ�\�����܂�.
	  @return �Ȃ�
	 */
	virtual void print_elapsed() {}

public:
	/**
	  �_�Q�̍��W�ϊ��s����t�@�C������ǂݍ��݂܂�.
	 */
	bool convert_coordinate(const char *filename) {
		if (!pcgen) return false;
		return pcgen->convert_coordinate(filename);
	}

	/**
	  �J������HMat����\�z���ꂽ���ۂ���Ԃ��܂�.���W�n�ϊ��ς݂�HMat����X�e���I�J�������\�z���Ă���\�������邽��	 */
	const bool is_camera_from_hmat() const {
		return (this->camtype == CamParamType::HMat) ? true : false;
	}

	/**
	  �摜�t�@�C������摜��ǂݍ���œ_�Q�������s���܂�.
	  @return �쐬���ꂽ�_�̐�
	  @param [in] filenames �摜�t�@�C���p�X(�_�Q�����ɕK�v�Ȗ����������i�[����Ă���悤�ɂ��Ă�������)
	  @param [in] is_interpo ��Ԃ��s�����ۂ�
	  @param [in] callback �_�Q������ɌĂяo�����R�[���o�b�N�֐�
	  @note filenames.size()�ŉ摜���A������Ă��邩�A�����łȂ����𔻒肵�܂�.
	 */
	int generate_pointcloud(std::vector<std::string> filenames, const bool is_interpo, PointCloudCallback *callback) {
		if (!load_images(filenames)) return false;
		return this->exec(is_interpo, callback);
	}

	/**
	  �摜�o�b�t�@����摜�����o���ē_�Q�������s���܂�.
	  @return �쐬���ꂽ�_�̐�
	  @param [in] buffers �摜����[�A�h���X���������i�[����Ă���x�N�^
	  @param [in] is_interpo ��Ԃ��s�����ۂ�
	  @param [in] callback �_�Q������ɌĂяo�����R�[���o�b�N�֐�
	  @note �摜�̓J���������荞�񂾂܂܂̂��̂�n���Ă�������.(���N�e�B�t�@�C���Ȃ��ŉ�����)
	  @note �摜�o�b�t�@�̐��������̃o�C�g���͓��͉摜�����Ɠ����ɂ��Ă�������.
	  @note ���E�����摜��n���ꍇ�́A��0, �E0, ��1, �E1, ... �̏��ɂȂ�悤���ׂĂ����Ă�������.
	  @note ���E�A���摜�͍����ɍ��J�����摜�A�E���ɉE�J�����摜�ƂȂ�悤�ɘA������Ă��邱�Ƃ�z�肵�Ă��܂�.
	  @note buffers.size()�ŉ摜���A������Ă��邩�A�����łȂ����𔻒肵�܂�.
	 */
	int generate_pointcloud(std::vector<unsigned char*> &buffers, const bool is_interpo, PointCloudCallback *callback) {
		if (!set_images(buffers)) return false;
		return this->exec(is_interpo, callback);
	
	}

protected:
	/**
	  ���}�b�v��̉摜������Ԃ��܂�
	  @return ���}�b�v��̉摜����
	 */
	const int get_image_cols(void) const { return settings.output_cols; }

	/**
	  ���}�b�v��̉摜�c����Ԃ��܂�
	  @return ���}�b�v��̉摜�c��
	 */
	const int get_image_rows(void) const { return settings.output_rows; }

	/**
	  �t�@�C������摜��ǂݍ���œ_�Q������ɓn���܂�.
	  @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	  @param [in] filenames �t�@�C���̃t���p�X���i�[����Ă���vector
	 */
	bool load_images(std::vector<std::string> &filenames);

	/**
	  �o�b�t�@����摜��_�Q������ɓn���܂�.
	  @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
	  @param [in] buffers �摜����[�A�h���X���i�[����Ă���vector
	 */
	bool set_images(std::vector<unsigned char*> &buffers);

	/**
	  �_�Q�𐶐����܂�.
	  @return �쐬���ꂽ�_�̐�
	  @param [in] callback �_�Q�쐬��ɌĂяo�����R�[���o�b�N�֐�
	 */
	int exec(const bool is_interpo, PointCloudCallback *callback);

	/**
	  �J�����摜�̉�����ݒ肵�܂�
	  @return �Ȃ�
	  @param [in] wd �J�����摜����
	 */
	void set_camera_cols(const int cols) {
		settings.input_cols = cols;

		// ���̏��A���N�e�B�t�@�C��̉摜�T�C�Y == ���͉摜�T�C�Y�Ƃ��Ă����^�p���Ă��Ȃ��̂�
		// �o�͉摜�T�C�Y�������l��ݒ肷��.���A�Ⴄ�l���ݒ�ł���̂ŖY��Ȃ��悤��...
		settings.output_cols = cols;
	}

	/**
	  �J�����摜�̏c����ݒ肵�܂�
	  @return �Ȃ�
	  @param [in] ht �J�����摜�c��
	 */
	void set_camera_rows(const int rows) {
		settings.input_rows = rows;

		// ���̏��A���N�e�B�t�@�C��̉摜�T�C�Y == ���͉摜�T�C�Y�Ƃ��Ă����^�p���Ă��Ȃ��̂�
		// �o�͉摜�T�C�Y�������l��ݒ肷��.���A�Ⴄ�l���ݒ�ł���̂ŖY��Ȃ��悤��...
		settings.output_rows = rows;
	}


protected:
	/// �J�����^�C�v
	CamParamType camtype;

	/// �X�e���I�J����
	iStereoCamera *stereo;

	/// �X�e���I�J�����쐬�̂��߂̐ݒ�
	StereoCameraSettings settings;

	/// �_�Q������
	iPointCloudGenerator *pcgen;

	/// �_�Q�v�Z���@
	iPointCloudGenerator::Method3D method3d;

	std::chrono::system_clock::duration elapsed_disparity;	///< �����v�Z�ɂ�����������
	std::chrono::system_clock::duration elapsed_genpcloud;	///< �_�Q�v�Z�ɂ�����������
};



class PLYSaver : public PointCloudCallback {
	std::string filename;
	bool status;

public:
	PLYSaver(const std::string name) : filename(name) {}

	const bool is_ok() const { return status; }
	const std::string get_filename() const { return filename; }

	/**
	  get_pointcloud�ɓn�����Ƃ��ɌĂяo�����callback�֐�(PLY�ɕۑ����܂�. �����ȓ_�͏��O���܂�.)
	  @note �ۑ��ɐ����������ۂ���status�ɕۑ�����܂�.
	 */
	void operator()(unsigned char *image, const size_t step, const int width, const int height,
		std::vector<Point3d> &points, const int n_valid);
};
