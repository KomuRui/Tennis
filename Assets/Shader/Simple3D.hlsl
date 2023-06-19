//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D		g_texture: register(t0);	        //�e�N�X�`���[
SamplerState	g_sampler : register(s0);	        //�T���v���[
SamplerState	g_texDepthSampler : register(s1);	//�T���v���[
Texture2D		g_texDepth : register(t2);          //�[�x�e�N�X�`���[

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

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUT
{
	float4 pos    : SV_POSITION;	//�ʒu
	float4 normal : TEXCOORD2;		//�@��
	float2 uv	  : TEXCOORD0;		//UV���W
	float4 eye	  : TEXCOORD1;		//����
	float4 norw   : TEXCOORD3;      //���[���h�}�g���N�X�����������@��
	float4 posw   : TEXCOORD4;      //���[���h�}�g���N�X�����������ʒu
	float4 LightTexCoord : TEXCOORD5;
	float4 LighViewPos	 : TEXCOORD6;
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUT VS(float4 pos : POSITION, float4 Normal : NORMAL, float2 Uv : TEXCOORD)
{
	//�s�N�Z���V�F�[�_�[�֓n�����
	VS_OUT outData;

	outData.posw = mul(pos, g_matWorld);

	//���[�J�����W�ɁA���[���h�E�r���[�E�v���W�F�N�V�����s���������
	//�X�N���[�����W�ɕϊ����A�s�N�Z���V�F�[�_�[��
	outData.pos = mul(pos, g_matWVP);		

	//�@���̕ό`
	Normal.w = 0;					            //4�����ڂ͎g��Ȃ��̂�0
	Normal = mul(Normal, g_matNormalTrans);		//�I�u�W�F�N�g���ό`����Ζ@�����ό`
	outData.normal = Normal;		            //������s�N�Z���V�F�[�_�[��
	outData.norw = mul(Normal, g_matWorld);

	//�����x�N�g���i�n�C���C�g�̌v�Z�ɕK�v
	float4 worldPos = mul(pos, g_matWorld);					    //���[�J�����W�Ƀ��[���h�s��������ă��[���h���W��
	outData.eye = normalize(g_vecCameraPosition - worldPos);	//���_���璸�_�ʒu�������Z�����������߂ăs�N�Z���V�F�[�_�[��

	//UV�u���W
	outData.uv = Uv;	//���̂܂܃s�N�Z���V�F�[�_�[��

	//���C�g�r���[���Q�Ƃ���Ƃ��A�肪����ƂȂ�e�N�X�`���[���W 
	outData.LightTexCoord = mul(pos, g_mWLPT); //���̓_���A���C�g�r���[�ł������Ƃ��̈ʒu���킩�� 

	//���C�g�r���[�ɂ�����ʒu(�ϊ���) 
	outData.LighViewPos = mul(pos, g_mWLP);

	//�܂Ƃ߂ďo��
	return outData;
}

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS(VS_OUT inData) : SV_Target
{
	//���C�g�̌���
	float4 lightDir = g_vecLightDir;	//�O���[�o���ϐ��͕ύX�ł��Ȃ��̂ŁA�������񃍁[�J���ϐ���
	lightDir = normalize(lightDir);     //�����������K�v�Ȃ̂Ő��K��

	//�@���̓s�N�Z���V�F�[�_�[�Ɏ����Ă������_�ŕ⊮���꒷�����ς���Ă���
	//���K�����Ă����Ȃ��Ɩʂ̖��邳�����������Ȃ�
	inData.normal.w = 0;
	inData.normal = normalize(inData.normal);

	float4 shade = saturate(dot(-lightDir, inData.normal));
	shade.a = 1;

	if (g_isBrightness != 0)
		shade = float4(g_isBrightness, g_isBrightness, g_isBrightness, 1.0f);

	float4 diffuse;
	//�e�N�X�`���L��
	if (g_isTexture == true)
	{
		//�e�N�X�`���̐F
		diffuse = g_texture.Sample(g_sampler, inData.uv);
	}
	else
	{
		//�}�e���A���̐F
		diffuse = g_vecDiffuse;
	}

	//�����i�A���r�G���g�j
	//�����Maya���Ŏw�肵�A�O���[�o���ϐ��Ŏ󂯎�������̂����̂܂�
	float4 	ambient = g_vecAmbient;

	//���ʔ��ˌ��i�X�y�L�����[�j
	float4 speculer = g_isSpeculerColor;	//�Ƃ肠�����n�C���C�g�͖����ɂ��Ă����āc

	if (g_isBrightness == 0)
	{
		if (speculer.a != 0)	//�X�y�L�����[�̏�񂪂����
		{
			float4 R = reflect(lightDir, inData.normal);		//�����˃x�N�g��
			speculer = pow(saturate(dot(R, inData.eye)), g_shuniness) * g_vecSpeculer;	//�n�C���C�g�����߂�
		}
	}

	//�ŏI�I�ȐF
	float4 color = diffuse * shade + diffuse * ambient + speculer;
	color += g_isAmbient;

	//�������g�ɉe��K�p����Ȃ�
	if (g_isShadowApply)
	{
		//�e�̏��� 
		inData.LightTexCoord /= inData.LightTexCoord.w;
		float TexValue = g_texDepth.Sample(g_texDepthSampler, inData.LightTexCoord).r;

		float LightLength = inData.LighViewPos.z / inData.LighViewPos.w;
		if (TexValue + 0.003 >= LightLength) //���C�g�r���[�ł̒������Z���i���C�g�r���[�ł͎Օ���������j 
		{
			color *= 0.6; //�e�i���邳�� 60%�j 
		}
		else
		{
			color *= 2.0f;
		}
	}
	else
	{
		color *= 2.0f;
	}

	//�����A���t�@�l���������ł������łȂ����
	if (diffuse.a == 1)
		color.a = g_isDiffuse;
	else
		color.a = diffuse.a;

	return color;
}