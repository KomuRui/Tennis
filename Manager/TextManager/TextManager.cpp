#include "TextManager.h"
#include "../GameManager/GameManager.h"
#include <map>

//�萔
namespace
{
	//�t�@�C���l�[���ɕK�v�ȏ��
	struct FNAME_LIST {
		int ID;
		std::string NAME;
	};

	//�V�[����ID�ƃt�@�C���p�X�l�[���̐ݒ�
	static const FNAME_LIST FNAME[] = {
		{ SCENE_ID_TITLE, "Tutorial/MobTalk1" },
	};

	//�t�@�C���p�X�ɋ��ʂ��ĕK�v�Ȃ���
	static const std::string PATH = "Stage/";
}

/// <summary>
/// ���{��̃e�L�X�g�Ǘ�
/// </summary>
namespace TextManager
{
	//���{��\�����邽�߂̘A�z�z��
	std::map<wchar_t, int> text;

	//������
	void TextManager::Initialize()
	{
		///////////////////////////�e�����̔ԍ�������//////////////////////////////

		text[L'��'] = 0;  text[L'��'] = 1; text[L'��'] = 2; text[L'��'] = 3; text[L'��'] = 4;
		text[L'��'] = 5;  text[L'��'] = 6; text[L'��'] = 7; text[L'��'] = 8; text[L'��'] = 9;
		text[L'��'] = 10; text[L'��'] = 11;text[L'��'] = 12;text[L'��'] = 13;text[L'��'] = 14;
		text[L'��'] = 15; text[L'��'] = 16;text[L'��'] = 17;text[L'��'] = 18;text[L'��'] = 19;
		text[L'��'] = 20; text[L'��'] = 21;text[L'��'] = 22;text[L'��'] = 23;text[L'��'] = 24;
		text[L'��'] = 25; text[L'��'] = 26;text[L'��'] = 27;text[L'��'] = 28;text[L'��'] = 29;
		text[L'��'] = 30; text[L'��'] = 31;text[L'��'] = 32;text[L'��'] = 33;text[L'��'] = 34;
		text[L'��'] = 35; text[L'��'] = 36;text[L'��'] = 37;					   
		text[L'��'] = 38; text[L'��'] = 39;text[L'��'] = 40;text[L'��'] = 41;text[L'��'] = 42;
		text[L'��'] = 43; text[L'��'] = 44;text[L'��'] = 45;					   
		text[L'��'] = 46; text[L'��'] = 47;text[L'��'] = 48;					   
		text[L'�A'] = 49; text[L'�C'] = 50;text[L'�E'] = 51;text[L'�G'] = 52;text[L'�I'] = 53;
		text[L'�J'] = 54; text[L'�L'] = 55;text[L'�N'] = 56;text[L'�P'] = 57;text[L'�R'] = 58;
		text[L'�T'] = 59; text[L'�V'] = 60;text[L'�X'] = 61;text[L'�Z'] = 62;text[L'�\'] = 63;
		text[L'�^'] = 64; text[L'�`'] = 65;text[L'�c'] = 66;text[L'�e'] = 67;text[L'�g'] = 68;
		text[L'�i'] = 69; text[L'�j'] = 70;text[L'�k'] = 71;text[L'�l'] = 72;text[L'�m'] = 73;
		text[L'�n'] = 74; text[L'�q'] = 75;text[L'�t'] = 76;text[L'�w'] = 77;text[L'�z'] = 78;
		text[L'�}'] = 79; text[L'�~'] = 80;text[L'��'] = 81;text[L'��'] = 82;text[L'��'] = 83;
		text[L'��'] = 84; text[L'��'] = 85;text[L'��'] = 86;					   
		text[L'��'] = 87; text[L'��'] = 88;text[L'��'] = 89;text[L'��'] = 90;text[L'��'] = 91;
		text[L'��'] = 92; text[L'��'] = 93;text[L'��'] = 94;					   
		text[L'��'] = 95; text[L'��'] = 96;text[L'��'] = 97;					   
		text[L'a']  = 98; text[L'b']  = 99;text[L'c'] = 100;text[L'd'] = 101;text[L'e'] = 102;
		text[L'f'] = 103; text[L'g'] = 104;text[L'h'] = 105;text[L'i'] = 106;text[L'j'] = 107;
		text[L'k'] = 108; text[L'l'] = 109;text[L'm'] = 110;text[L'n'] = 111;text[L'o'] = 112;
		text[L'p'] = 113; text[L'q'] = 114;text[L'r'] = 115;text[L's'] = 116;text[L't'] = 117;
		text[L'u'] = 118; text[L'v'] = 119;text[L'w'] = 120;text[L'x'] = 121;text[L'y'] = 122;
		text[L'z'] = 123;													  
		text[L'A'] = 124; text[L'B'] = 125;text[L'C'] = 126;text[L'D'] = 127;text[L'E'] = 128;
		text[L'F'] = 129; text[L'G'] = 130;text[L'H'] = 131;text[L'I'] = 132;text[L'J'] = 133;
		text[L'K'] = 134; text[L'L'] = 135;text[L'M'] = 136;text[L'N'] = 137;text[L'O'] = 138;
		text[L'P'] = 139; text[L'Q'] = 140;text[L'R'] = 141;text[L'S'] = 142;text[L'T'] = 143;
		text[L'U'] = 144; text[L'V'] = 145;text[L'W'] = 146;text[L'X'] = 147;text[L'Y'] = 148;
		text[L'Z'] = 149;													  
		text[L'!'] = 150; text[L'%'] = 151;text[L'('] = 152;text[L')'] = 153;text[L'*'] = 154;
		text[L'+'] = 155; text[L','] = 156;text[L'-'] = 157;text[L'.'] = 158;text[L'/'] = 159;
		text[L':'] = 160; text[L';'] = 161;text[L'<'] = 162;text[L'>'] = 163;text[L'?'] = 164;
		text[L'@'] = 165; text[L'['] = 166;text[L']'] = 167;text[L'_'] = 168;text[L'{'] = 169;
		text[L'}'] = 170;													  
		text[L'0'] = 171; text[L'1'] = 172;text[L'2'] = 173;text[L'3'] = 174;text[L'4'] = 175;
		text[L'5'] = 176; text[L'6'] = 177;text[L'7'] = 178;text[L'8'] = 179;text[L'9'] = 180;
		text[L'��'] = 192;text[L'��'] = 193;text[L'��'] = 194;text[L'��'] = 195;text[L'��'] = 196;
		text[L'��'] = 197;text[L'��'] = 198;text[L'��'] = 199;text[L'��'] = 200;text[L'��'] = 201;
		text[L'��'] = 202;text[L'��'] = 203;text[L'��'] = 204;text[L'��'] = 205;
		text[L'��'] = 206;text[L'��'] = 207;text[L'��'] = 208;text[L'��'] = 209;text[L'��'] = 210;
		text[L'�K'] = 211;text[L'�M'] = 212;text[L'�O'] = 213;text[L'�Q'] = 214;text[L'�S'] = 215;
		text[L'�U'] = 216;text[L'�W'] = 217;text[L'�Y'] = 218;text[L'�['] = 219;text[L'�]'] = 220;
		text[L'�_'] = 221;text[L'�d'] = 222;text[L'�f'] = 223;text[L'�h'] = 224;
		text[L'�o'] = 225;text[L'�r'] = 226;text[L'�u'] = 227;text[L'��'] = 228;text[L'�{'] = 229;
		text[L'��'] = 230;text[L'��'] = 231;text[L'��'] = 232;text[L'��'] = 233;text[L'��'] = 234;
		text[L'�p'] = 235;text[L'�s'] = 236;text[L'�v'] = 237;text[L'�y'] = 238;text[L'�|'] = 239;

	}

	//�����̑Ή�����ԍ����擾
	int TextManager::GetNumber(wchar_t t) { return text[t]; }

	//�V�[��ID���Q�b�g
	std::string TextManager::GetText(SCENE_ID nowId) { return PATH + FNAME[nowId].NAME + ".csv"; }
}