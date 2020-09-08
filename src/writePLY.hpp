#pragma once

#include <string>
#include "iPointCloudGenerator.hpp"

/**
 * �_�Q�f�[�^��PLY�`���Ńt�@�C���ɕۑ����܂�.
 * @return �����ɐ��������ꍇ��true, ���s�����ꍇ��false.
 * @param [in] filename �o�͐�t�@�C����
 * @param [in] cloud �_�Q�f�[�^�o�b�t�@�擪�A�h���X
 * @param [in] n_point ���_��
 * @param [in] rgrid �����W�O���b�h�f�[�^�o�b�t�@�擪�A�h���X(�o�͂��Ȃ��ꍇ��0)
 * @param [in] width �����W�O���b�h�f�[�^�̉���
 * @param [in] height �����W�O���b�h�f�[�^�̏c��
 */
bool writePLY(const std::string filename, const PointCloudElement *cloud, const int n_point,
	const unsigned int *rgrid = 0, const int width = 0, const int height = 0);
