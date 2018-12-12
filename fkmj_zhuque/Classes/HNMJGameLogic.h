#pragma once

#include "CMD_HNMJ.h"
#include "GameDefine.h"
#include "FvSingleton.h"

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//�߼�����

#define	MASK_COLOR					0xF0								//��ɫ����
#define	MASK_VALUE					0x0F								//��ֵ����

//////////////////////////////////////////////////////////////////////////
//��������

//������־
#define WIK_NULL					0x00000000								//û������
#define WIK_LEFT					0x00000001								//�������
#define WIK_CENTER				0x00000002								//�г�����
#define WIK_RIGHT					0x00000004								//�ҳ�����
#define WIK_PENG					0x00000008								//��������
#define WIK_GANG					0x00000010								//��������
#define WIK_XIAO_HU				0x00000020								//С��								
#define WIK_CHI_HU				0x00000040								//�Ժ�����
#define WIK_ZI_MO					0x00000080								//����
#define WIK_BU_ZHANG				0x00000100								//����
#define WIK_CS_GANG				0x00000200								//��ɳ��
//////////////////////////////////////////////////////////////////////////
//���ƶ���

//����
#define CHK_NULL					0x00										//�Ǻ�����
#define CHK_CHI_HU					0x01										//������


// ���
#define CHR_PENGPENG_HU						0x00000001								//������
#define CHR_JIANGJIANG_HU					0x00000002									//������
#define CHR_QING_YI_SE						0x00000004									//��һɫ
#define CHR_HAI_DI_LAO						0x00000008									//������
#define CHR_HAI_DI_PAO						0x00000010									//������
#define CHR_QI_XIAO_DUI						0x00000020									//��С��
#define CHR_HAOHUA_QI_XIAO_DUI				0x00000040									//������С��
#define CHR_GANG_KAI						0x00000080									//���Ͽ���
#define CHR_QIANG_GANG_HU					0x00000100									//���ܺ�
#define CHR_GANG_SHANG_PAO					0x00000200									//������
#define CHR_QUAN_QIU_REN					0x00000400									//ȫ����
#define CHR_SHUANG_HAOHUA_QI_XIAO_DUI		0x00000800									//˫������С��
#define CHR_HONGZHONG_WU					0x00001000									//�޺��ж��һ��
#define CHR_GANG_SHUANG_KAI					0x00002000									//��ɳ˫�ܿ�

//С��
#define CHR_XIAO_DA_SI_XI					0x00004000									//����ϲ
#define CHR_XIAO_BAN_BAN_HU					0x00008000									//����
#define CHR_XIAO_QUE_YI_SE					0x00010000									//ȱһɫ
#define CHR_XIAO_LIU_LIU_SHUN				0x00020000									//����˳

#define CHR_ZI_MO							0x01000000									//����
#define CHR_SHU_FAN						0x02000000									//�ط�
#define CHR_TIAN_HU						0x04000000									//���

//�˿˶���
#define HEAP_FULL_COUNT				26									//����ȫ��

#define MAX_RIGHT_COUNT				1	
//////////////////////////////////////////////////////////////////////////


namespace HNMJ
{

	//��������
	struct tagKindItem
	{
		DWORD							cbWeaveKind;						//�������
		BYTE							cbCenterCard;						//�����˿�
		BYTE							cbCardIndex[3];						//�˿�����
		BYTE							cbValidIndex[3];					//ʵ���˿�����
	};

	//�������
	struct tagWeaveItem
	{
		DWORD							cbWeaveKind;						//�������
		BYTE							cbCenterCard;						//�����˿�
		BYTE							cbPublicCard;						//������־
		WORD							wProvideUser;						//��Ӧ�û�
	};

	//���ƽ��
	struct tagGangCardResult
	{
		BYTE							cbCardCount;						//�˿���Ŀ
		BYTE							cbCardData[4];						//�˿�����
	};

	//��������
	struct tagAnalyseItem
	{
		BYTE							cbCardEye;							//�����˿�
		bool                            bMagicEye;                          //�����Ƿ�������
		DWORD							cbWeaveKind[4];						//�������
		BYTE							cbCenterCard[4];					//�����˿�
		BYTE                            cbCardData[4][4];                   //ʵ���˿�
		BYTE                            cbMagicIdex[MAX_INDEX];             //�����滻����
	};
	//////////////////////////////////////////////////////////////////////////

	/*
	//	Ȩλ�ࡣ
	//  ע�⣬�ڲ�����λʱ���ֻ��������Ȩλ.����
	//  CChiHuRight chr;
	//  chr |= (chr_zi_mo|chr_peng_peng)������������޶���ġ�
	//  ֻ�ܵ�������:
	//  chr |= chr_zi_mo;
	//  chr |= chr_peng_peng;
	*/
	class CChiHuRight
	{	
		//��̬����
	private:
		static bool						m_bInit;
		static dword					m_dwRightMask[MAX_RIGHT_COUNT];

		//Ȩλ����
	private:
		dword							m_dwRight[MAX_RIGHT_COUNT];

	public:
		//���캯��
		CChiHuRight();

		//���������
	public:
		//��ֵ��
		CChiHuRight & operator = ( dword dwRight );

		//�����
		CChiHuRight & operator &= ( dword dwRight );
		//�����
		CChiHuRight & operator |= ( dword dwRight );

		//��
		CChiHuRight operator & ( dword dwRight );
		CChiHuRight operator & ( dword dwRight ) const;

		//��
		CChiHuRight operator | ( dword dwRight );
		CChiHuRight operator | ( dword dwRight ) const;

		//���ܺ���
	public:
		//�Ƿ�ȨλΪ��
		bool IsEmpty();

		//����ȨλΪ��
		void SetEmpty();

		//��ȡȨλ��ֵ
		BYTE GetRightData( dword dwRight[], BYTE cbMaxCount );

		//����Ȩλ��ֵ
		bool SetRightData( const dword dwRight[], BYTE cbRightCount );

	private:
		//���Ȩλ�Ƿ���ȷ
		bool IsValidRight( dword dwRight );
	};


	//////////////////////////////////////////////////////////////////////////

//	typedef CWHArray<tagAnalyseItem,tagAnalyseItem &> CAnalyseItemArray;
	typedef std::vector<tagAnalyseItem> AnalyseItemList;
	//����˵��

	//��Ϸ�߼���
	class CGameLogic: public FvSingleton<CGameLogic>
	{
		//��������
	protected:
		static const BYTE				m_cbCardDataArray[MAX_REPERTORY];	//�˿�����
		BYTE							m_cbMagicIndex;						//��������

		//��������
	public:
		//���캯��
		CGameLogic();
		//��������
		virtual ~CGameLogic();

		//���ƺ���
	public:
		//�����˿�
		void RandCardData(BYTE cbCardData[], BYTE cbMaxCount);
		//ɾ���˿�
		bool RemoveCard(BYTE cbCardIndex[MAX_INDEX], BYTE cbRemoveCard);
		//ɾ���˿�
		bool RemoveCard(BYTE cbCardIndex[MAX_INDEX], const BYTE cbRemoveCard[], BYTE cbRemoveCount);
		//ɾ���˿�
		bool RemoveValueCard(BYTE cbCardData[], BYTE cbCardCount, const BYTE cbRemoveCard[], BYTE cbRemoveCount);
		//ɾ���˿�
		BYTE RemoveValueCardAll(BYTE cbCardData[], BYTE cbCardCount,BYTE cbRemoveCard);
		//ɾ���˿�
		bool RemoveValueCardOne(BYTE cbCardData[], BYTE cbCardCount,BYTE cbRemoveCard);
		//��������
		void SetMagicIndex( BYTE cbMagicIndex ) { m_cbMagicIndex = cbMagicIndex; }
		//����
		bool IsMagicCard( BYTE cbCardData );

		//��������
	public:
		//��Ч�ж�
		bool IsValidCard(BYTE cbCardData);
		//�˿���Ŀ
		BYTE GetCardCount(const BYTE cbCardIndex[MAX_INDEX]);
		//����˿�
		BYTE GetWeaveCard(BYTE cbWeaveKind, BYTE cbCenterCard, BYTE cbCardBuffer[4]);

		//�ȼ�����
	public:
		//�����ȼ�
		BYTE GetUserActionRank(BYTE cbUserAction);
		//���Ƶȼ�
		WORD GetChiHuActionRank(const CChiHuRight & ChiHuRight);

		//�����ж�
	public:
		//�����ж�
		BYTE EstimateEatCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);
		//�����ж�
		BYTE EstimatePengCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);
		//�����ж�
		BYTE EstimateGangCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard);

		//�����ж�
	public:
		//���Ʒ���
		BYTE AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult,BYTE cbGameType);
		//�Ժ�����
		BYTE AnalyseChiHuCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, BYTE cbCurrentCard, CChiHuRight &ChiHuRight);
		//���Ʒ���
		BYTE AnalyseTingCard( const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount );
		//�Ƿ�����
		bool IsTingCard( const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount );
		//�Ƿ���
		bool IsHuaZhu( const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount );
		
		//���Ʒ���
		BYTE AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult);

		//ת������
	public:
		//�˿�ת��
		BYTE SwitchToCardData(BYTE cbCardIndex);
		//�˿�ת��
		BYTE SwitchToCardIndex(BYTE cbCardData);
		//�˿�ת��
		BYTE SwitchToCardData(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCardData[MAX_COUNT]);
		//�˿�ת��
		BYTE SwitchToCardIndex(const BYTE cbCardData[], BYTE cbCardCount, BYTE cbCardIndex[MAX_INDEX]);


		//����,������ֵ����
		bool SortCardList( BYTE cbCardData[MAX_COUNT], BYTE cbCardCount );
		//��������
	protected:
		//�����
		bool IsPengPeng( const tagAnalyseItem *pAnalyseItem );
		//��һɫ��
		bool IsQingYiSe(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[], const BYTE cbItemCount,const BYTE cbCurrentCard);

		bool IsDanDiao(const BYTE cbCardIndex[MAX_INDEX],const BYTE cbCurrentCard);
		//��С����
		bool IsQiXiaoDui(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[],const  BYTE cbWeaveCount,const BYTE cbCurrentCard);
		//����
		bool IsDaiYao( const tagAnalyseItem *pAnalyseItem );
		//����
		bool IsJiangDui( const tagAnalyseItem *pAnalyseItem );
	public:
		BYTE GetCardColor(BYTE cbCardDat);
		BYTE GetCardValue(BYTE cbCardDat);

	public:
		//�����˿�
		bool AnalyseCard(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount, AnalyseItemList & kAnalyseItemList);
		bool isGangTingCS(const BYTE cbCardIndex[MAX_INDEX],const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount,BYTE cbCard);
		bool IsJiangJiangHu(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[],const  BYTE cbWeaveCount,const BYTE cbCurrentCard);
		void getTingCardHZ(const BYTE cbCardIndex[MAX_INDEX],const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount,std::vector<BYTE>& kTingCardList);
		bool isTingCardCS(const BYTE cbCardIndex[MAX_INDEX],const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount);
	};
}
