#include "EffectManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include <fstream>
#include <map>

/// <summary>
/// �G�t�F�N�g���Ǘ�����
/// </summary>
namespace EffectManager
{
	//�ǂݍ��񂾃G�t�F�N�g��ۑ����Ă����e�[�u��
	//string : �G�t�F�N�g��ۑ����Ă���t�@�C���l�[��
	//EmitterData : �ǂݍ��񂾃G�t�F�N�g�̊e��f�[�^��ۑ����Ă���Ƃ���
	map<string, EmitterData> effectTable_;

	//�G�t�F�N�g�\��
	int Draw(string fileNamePath, XMFLOAT3 pos)
	{
		//���݂��Ă��邩�ǂ���
		bool isExist = false;

		//�����ɓo�^����Ă���G�t�F�N�g���ǂ������ׂ�
		for (auto it = effectTable_.begin(); it != effectTable_.end(); it++) {
			
			//�o�^����Ă���̂Ȃ�
			if (it->first == fileNamePath)
			{
				ARGUMENT_INITIALIZE(isExist, true);
				break;
			}
		}

		//���݂��Ă��Ȃ��̂Ȃ烍�[�h
        if (!isExist) Load(fileNamePath);

        //�|�W�V���������X�V
        ARGUMENT_INITIALIZE(effectTable_[fileNamePath].position, pos);

        //�G�t�F�N�g�X�^�[�g
        return VFX::Start(effectTable_[fileNamePath]);
	}

	//�G�t�F�N�g���[�h
	void Load(string fileNamePath)
	{
        //�t�@�C���I�[�v��
        std::ifstream ifs(fileNamePath);

        //�G�t�F�N�g�̃f�[�^
        EmitterData data;

        //�e�f�[�^��ۑ����Ă����p
        string info[44] = { "" };

        //�z��̌��Ă�ԍ�
        int index = 0;

        //�����܂œǂ�
        while (!ifs.eof())
        {
            //1��buf�Ɋi�[
            string str = { "" };
            std::getline(ifs, str);

            //str�̃T�C�Y�����[�v
            for (int i = 0; i < str.length(); i++)
            {
                //�e�p�����[�^�������data�Ɋi�[���Ă���
                if (str[i] != ',')
                {
                    info[index] += str[i];
                }
                else
                    index++;
            }
        }

        //�e�����
        ARGUMENT_INITIALIZE(data.textureFileName, info[0]);
        ARGUMENT_INITIALIZE(data.position, XMFLOAT3(std::stof(info[1]), std::stof(info[2]), std::stof(info[3])));
        ARGUMENT_INITIALIZE(data.positionRnd, XMFLOAT3(std::stof(info[4]), std::stof(info[5]), std::stof(info[6])));
        ARGUMENT_INITIALIZE(data.direction, XMFLOAT3(std::stof(info[7]), std::stof(info[8]), std::stof(info[9])));
        ARGUMENT_INITIALIZE(data.directionRnd, XMFLOAT3(std::stof(info[10]), std::stof(info[11]), std::stof(info[12])));
        ARGUMENT_INITIALIZE(data.speed, std::stof(info[13]));
        ARGUMENT_INITIALIZE(data.speedRnd, std::stof(info[14]));
        ARGUMENT_INITIALIZE(data.accel, std::stof(info[15]));
        ARGUMENT_INITIALIZE(data.gravity, std::stof(info[16]));
        ARGUMENT_INITIALIZE(data.color, XMFLOAT4(std::stof(info[17]), std::stof(info[18]), std::stof(info[19]), std::stof(info[20])));
        ARGUMENT_INITIALIZE(data.deltaColor, XMFLOAT4(std::stof(info[21]), std::stof(info[22]), std::stof(info[23]), std::stof(info[24])));
        ARGUMENT_INITIALIZE(data.rotate, XMFLOAT3(std::stof(info[25]), std::stof(info[26]), std::stof(info[27])));
        ARGUMENT_INITIALIZE(data.rotateRnd, XMFLOAT3(std::stof(info[28]), std::stof(info[29]), std::stof(info[30])));
        ARGUMENT_INITIALIZE(data.spin, XMFLOAT3(std::stof(info[31]), std::stof(info[32]), std::stof(info[33])));
        ARGUMENT_INITIALIZE(data.size, XMFLOAT2(std::stof(info[34]), std::stof(info[35])));
        ARGUMENT_INITIALIZE(data.sizeRnd, XMFLOAT2(std::stof(info[36]), std::stof(info[37])));
        ARGUMENT_INITIALIZE(data.scale, XMFLOAT2(std::stof(info[38]), std::stof(info[39])));
        ARGUMENT_INITIALIZE(data.lifeTime, std::stof(info[40]));
        ARGUMENT_INITIALIZE(data.delay, std::stof(info[41]));
        ARGUMENT_INITIALIZE(data.number, std::stof(info[42]));
        ARGUMENT_INITIALIZE(data.isBillBoard, std::stoi(info[43]));

        //�G�t�F�N�g�e�[�u���ɕۑ�
        ARGUMENT_INITIALIZE(effectTable_[fileNamePath],data);
	}
}