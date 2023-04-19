//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture: register(t0);	//�e�N�X�`���[
SamplerState	g_sampler : register(s0);	//�T���v���[

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	g_matWVP;			  // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matNormalTrans;	  // �@���̕ϊ��s��i��]�s��Ɗg��̋t�s��j
	float4x4	g_matWorld;			  // ���[���h�ϊ��s��
	float4		g_vecLightDir;		  // ���C�g�̕����x�N�g��
	float4		g_vecDiffuse;		  // �f�B�t���[�Y�J���[�i�}�e���A���̐F�j
	float4		g_vecAmbient;		  // �A���r�G���g�J���[�i�e�̐F�j
	float4		g_vecSpeculer;		  // �X�y�L�����[�J���[�i�n�C���C�g�̐F�j
	float4      g_isSpeculerColor;    // �C�ӂŌ��߂��X�y�L�����[�J���[
	float4		g_vecCameraPosition;  // ���_�i�J�����̈ʒu�j
	float4      g_vecLightPosition;   // ���C�g�̈ʒu
	float4      g_LightPosition[15];  // ���C�g�̌����̈ʒu
	float4      g_LightIntensity[15]; // ���C�g�̌����̋���
	float4      g_isAmbient;          // �A���r�G���g�̗͂̑傫�� 
	float4		g_outLineColor;		  //�A�E�g���C���̐F
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 normal : NORMAL, float2 uv : TEXCOORD)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	//�@��
	normal.w = 0;
	pos = pos + normal * 0.2f;
	outData.pos = mul(pos, g_matWVP);

	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	return g_outLineColor;
}