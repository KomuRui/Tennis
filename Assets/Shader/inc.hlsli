//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	float4x4	g_matWVP;			  // ���[���h�E�r���[�E�v���W�F�N�V�����̍����s��
	float4x4	g_matNormalTrans;	  // �@���̕ϊ��s��i��]�s��Ɗg��̋t�s��j
	float4x4	g_matWorld;			  // ���[���h�ϊ��s��
	float4x4	g_mWLP;				  //���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����̍��� 
	float4x4	g_mWLPT;			  //���[���h�E�h���C�g�r���[�h�E�v���W�F�N�V�����EUV �s��̍��� 
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
	float4		g_outLineColor;		  // �A�E�g���C���̐F
	float		g_shuniness;		  // �n�C���C�g�̋����i�e�J����j
	bool		g_isTexture;		  // �e�N�X�`���\���Ă��邩�ǂ���
	bool        g_isShadowApply;      // �������g�ɉe��K�p���邩
	float 		g_isDiffuse;		  // �����ɂ��邩
	float       g_isBrightness;       // ���邳
};