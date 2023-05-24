#include "EffectManager.h"
#include "../../Engine/ResourceManager/VFX.h"
#include <fstream>
#include <map>

/// <summary>
/// エフェクトを管理する
/// </summary>
namespace EffectManager
{
	//読み込んだエフェクトを保存しておくテーブル
	//string : エフェクトを保存してあるファイルネーム
	//EmitterData : 読み込んだエフェクトの各種データを保存してあるところ
	map<string, EmitterData> effectTable_;

	//エフェクト表示
	int Draw(string fileNamePath, XMFLOAT3 pos)
	{
		//存在しているかどうか
		bool isExist = false;

		//既存に登録されているエフェクトかどうか調べる
		for (auto it = effectTable_.begin(); it != effectTable_.end(); it++) {
			
			//登録されているのなら
			if (it->first == fileNamePath)
			{
				ARGUMENT_INITIALIZE(isExist, true);
				break;
			}
		}

		//存在していないのならロード
        if (!isExist) Load(fileNamePath);

        //ポジションだけ更新
        ARGUMENT_INITIALIZE(effectTable_[fileNamePath].position, pos);

        //エフェクトスタート
        return VFX::Start(effectTable_[fileNamePath]);
	}

	//エフェクトロード
	void Load(string fileNamePath)
	{
        //ファイルオープン
        std::ifstream ifs(fileNamePath);

        //エフェクトのデータ
        EmitterData data;

        //各データを保存しておく用
        string info[44] = { "" };

        //配列の見てる番号
        int index = 0;

        //末尾まで読む
        while (!ifs.eof())
        {
            //1列bufに格納
            string str = { "" };
            std::getline(ifs, str);

            //strのサイズ分ループ
            for (int i = 0; i < str.length(); i++)
            {
                //各パラメータを一つずつdataに格納していく
                if (str[i] != ',')
                {
                    info[index] += str[i];
                }
                else
                    index++;
            }
        }

        //各情報代入
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

        //エフェクトテーブルに保存
        ARGUMENT_INITIALIZE(effectTable_[fileNamePath],data);
	}
}