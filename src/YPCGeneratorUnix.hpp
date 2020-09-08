#pragma once

#include <vector>
#include <string>

//2020/08/25 modified by hato ---------- start ----------
#ifdef YAML_PARAM
//2020/08/25 modified by hato ----------  end  ----------
#include <yaml-cpp/yaml.h>
//2020/08/25 modified by hato ---------- start ----------
#endif
//2020/08/25 modified by hato ----------  end  ----------

//2020/08/26 modified by hato ---------- start ----------
#include <map>
//2020/08/26 modified by hato ----------  end ----------

#include "YPCGenerator.hpp"

class YPCGeneratorUnix : public YPCGenerator {
protected:
	PcGenMode pcgen_mode;

public:
	YPCGeneratorUnix() : pcgen_mode(PcGenMode::PCGEN_MULTI) {}
	virtual ~YPCGeneratorUnix() {
		if (stereo) stereo->destroy();
		stereo = 0;
		if (pcgen) pcgen->destroy();
		pcgen = 0;
	}

	/// �_�Q��������쐬����.
	bool create_pcgen(const PcGenMode pcgen_mode);

	/// �p�����[�^�̏�����
	//2020/08/26 modified by hato ---------- start ----------
#ifdef YAML_PARAM
	bool init(const char* cfgpath);
#endif
	bool init(std::map<std::string,double> &paramMap);
	//2020/08/26 modified by hato ----------  end  ----------

	/// �X�e���I�J�����쐬
	bool create_camera(const char* dirname);
	bool create_camera_raw(
		std::vector<double> &Kl, std::vector<double> &Kr,
		std::vector<double> &Dl, std::vector<double> &Dr,
		std::vector<double> &R, std::vector<double> &T);

	/// ���̓t�@�C�������X�g�쐬
	std::vector<std::string> create_filelist(const char* dirname, const char* ext);
	

	
	/**
	  �_�Q��������PLY�t�@�C���ۑ����s���܂�
	  @param [in] filelist ���͉摜�t�@�C�������X�g
	  @param [in] outpath PLY�t�@�C����
	  @param [in] is_interpo ��Ԃ��s�����ۂ�
	 */
	bool generate_pointcloud(std::vector<std::string> &filelist, const char* outpath, const bool is_interpo);
	
//2020/08/25 modified by hato ---------- start ----------
	/**
	  �_�Q��������PLY�t�@�C���ۑ����s���܂�
	  @param [in] cam_imgs ���E�J�����摜
	  @param [in] outpath PLY�t�@�C����
	  @param [in] is_interpo ��Ԃ��s�����ۂ�
	 */
	int generate_pointcloud(std::vector<unsigned char*>& cam_imgs, const bool is_interpo,PointCloudCallback*callback);

//2020/08/25 modified by hato ----------  end  ----------

//2020/08/26 modified by hato ---------- start ----------
	///< �����v�Z�ɂ�����������
	std::chrono::system_clock::duration get_elapsed_disparity(){
		return this->elapsed_disparity;
	}
	
	///< �_�Q�v�Z�ɂ�����������
	std::chrono::system_clock::duration get_elapsed_genpcloud(){
		return this->elapsed_genpcloud;
	}
//2020/08/26 modified by hato ---------- end ----------
	
private:
//2020/08/25 modified by hato ---------- start ----------
#ifdef YAML_PARAM
//2020/08/25 modified by hato ----------  end  ----------
	/// SGBM�̐ݒ�l��ǂݍ���Őݒ肵�܂�.
	bool _init_SGBM(const YAML::Node& param);

	// Gray�R�[�h�ʑ��V�t�g
	bool _init_PSFT(const YAML::Node& param);

	// �}���`�ʑ��V�t�g
	bool _init_MPSFT(const YAML::Node& param);
//2020/08/25 modified by hato ---------- start ----------
#endif
//2020/08/25 modified by hato ----------  end  ----------

//2020/08/26 modified by hato ---------- start ----------
	bool _init_SGBM(std::map<std::string,double>& p);
	bool _init_PSFT(std::map<std::string,double>& p);
	bool _init_MPSFT(std::map<std::string,double>& p);
//2020/08/26 modified by hato ----------  end  ----------
};
