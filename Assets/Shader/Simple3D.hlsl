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
	float		g_shuniness;		  // �n�C���C�g�̋����i�e�J����j
	bool		g_isTexture;		  // �e�N�X�`���\���Ă��邩�ǂ���
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

	float3 dir = float3(0,0,0);
	float3 sumDir = float3(0, 0, 0); //���ׂĂ̌����̕������l����������
	float  len = 0;
	float  colD = 0;
	float  colA = 0;
	float  col = 0;
	float4 shade = float4(0,0,0,0);

	for (int i = 0; i < 8; i++)
	{
		if (g_LightPosition[i].x != 99999 && g_LightPosition[i].y != 99999 && g_LightPosition[i].z != 99999)
		{
			//�_�����̕���
			dir = g_LightPosition[i].xyz - inData.posw.xyz;

			//�_�����̋���
			len = length(dir) / g_LightIntensity[i];

			//�_�����̕�����normalize
			dir = normalize(dir);

			//�����𑫂�
			sumDir += dir;
			sumDir = normalize(sumDir);

			//�g�U
			colD = saturate(dot(normalize(inData.normal), dir)) * g_LightIntensity[i];

			//����
			colA = saturate(1.0f / (1.0 + 0 * len + 0.2 * len * len));

			col += colD * colA;
		}
	}

	if (col > 1)
		col = 1;

	if (g_isBrightness == 0)
		shade = float4(col, col, col, 1.0f);
	else
		shade = float4(g_isBrightness, g_isBrightness, g_isBrightness, 1.0f);


	float4 d = float4(sumDir.x, sumDir.y, sumDir.z, 0);

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
		if (g_vecSpeculer.a != 0)	//�X�y�L�����[�̏�񂪂����
		{
			float4 R = reflect(d, inData.normal);			//�����˃x�N�g��
			speculer = pow(saturate(dot(R, inData.eye)), g_shuniness) * g_vecSpeculer;	//�n�C���C�g�����߂�
		}
	}

	//�ŏI�I�ȐF
	float4 color = diffuse * shade + diffuse * ambient + speculer;
	color += g_isAmbient;
	color.a = g_isDiffuse;

	return color;
}