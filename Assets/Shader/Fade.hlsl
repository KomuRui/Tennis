//������������������������������������������������������������������������������
 // �e�N�X�`�����T���v���[�f�[�^�̃O���[�o���ϐ���`
//������������������������������������������������������������������������������
Texture2D g_texture : register(t0);	// �e�N�X�`���[
SamplerState g_sampler : register(s0); // �e�N�X�`���[�T���v���[

//������������������������������������������������������������������������������
 // �R���X�^���g�o�b�t�@
// DirectX �����瑗�M����Ă���A�|���S�����_�ȊO�̏����̒�`
//������������������������������������������������������������������������������
cbuffer global
{
	matrix g_matWorld;		// ���_���W�ϊ��s��
	matrix g_matTexture;	// �e�N�X�`�����W�ϊ��s��
	float4 g_vecColor;		// �e�N�X�`�������F
	float  g_distance;      // �`�拗��
	float  g_screenWidth;   // �X�N���[���̉�
	float  g_screenHeight;  // �X�N���[���̏c
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_�[�o�́��s�N�Z���V�F�[�_�[���̓f�[�^�\����
//������������������������������������������������������������������������������
struct VS_OUTPUT
{
	float4 pos	: SV_POSITION;	// �ʒu
	float2 uv	: TEXCOORD;		// UV���W
};

//������������������������������������������������������������������������������
// ���_�V�F�[�_
//������������������������������������������������������������������������������
VS_OUTPUT VS(float4 pos : POSITION, float4 uv : TEXCOORD)
{
	VS_OUTPUT output;
	output.pos = mul(pos, g_matWorld);
	output.uv = mul(uv, g_matTexture);
	return output;
}

//////////////////////////////////FadeIn�p///////////////////////////////////////////

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS_FadeIn(VS_OUTPUT input) : SV_Target
{
	float4 diffuse = g_texture.Sample(g_sampler, input.uv);
	float Alpha = diffuse.a;

	float dis = ((input.pos.x - g_screenWidth) * (input.pos.x - g_screenWidth)) + ((input.pos.y - g_screenHeight) * (input.pos.y - g_screenHeight));

	//�`�拗����菬�����Ȃ�
	if ((g_distance * g_distance) > dis)
	{
		float4 color = g_vecColor * diffuse;
		color.a = 0;

		return color;
	}
	else
	{
		float4 color = g_vecColor * diffuse;
		color.a = 1;

		return color;
	}
}

//////////////////////////////////FadeOut�p///////////////////////////////////////////

//������������������������������������������������������������������������������
// �s�N�Z���V�F�[�_
//������������������������������������������������������������������������������
float4 PS_FadeOut(VS_OUTPUT input) : SV_Target
{
	float4 diffuse = g_texture.Sample(g_sampler, input.uv);
	float Alpha = diffuse.a;

	float dis = ((input.pos.x - g_screenWidth) * (input.pos.x - g_screenWidth)) + ((input.pos.y - g_screenHeight) * (input.pos.y - g_screenHeight));

	//�`�拗����菬�����Ȃ�
	if ((g_distance * g_distance) > dis)
	{
		float4 color = g_vecColor * diffuse;
		color.a = 1;

		return color;
	}
	else
	{
		float4 color = g_vecColor * diffuse;
		color.a = 0;

		return color;
	}

}
