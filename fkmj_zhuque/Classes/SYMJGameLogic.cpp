#include "SYMJGameLogic.h"

//////////////////////////////////////////////////////////////////////////

FV_SINGLETON_STORAGE(SYMJ::CGameLogic);
namespace SYMJ
{
	//��̬����
	bool		CChiHuRight::m_bInit = false;
	dword		CChiHuRight::m_dwRightMask[MAX_RIGHT_COUNT];

	//���캯��
	CChiHuRight::CChiHuRight()
	{
		zeromemory( m_dwRight,sizeof(m_dwRight) );

		if( !m_bInit )
		{
			m_bInit = true;
			for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
			{
				if( 0 == i )
					m_dwRightMask[i] = 0;
				else
					m_dwRightMask[i] = (dword(pow((float)2,(float)(i-1))))<<28;
			}
		}
	}

	//��ֵ������
	CChiHuRight & CChiHuRight::operator = ( dword dwRight )
	{
		dword dwOtherRight = 0;
		//��֤Ȩλ
		if( !IsValidRight( dwRight ) )
		{
			//��֤ȡ��Ȩλ
			ASSERT( IsValidRight( ~dwRight ) );
			if( !IsValidRight( ~dwRight ) ) return *this;
			dwRight = ~dwRight;
			dwOtherRight = MASK_CHI_HU_RIGHT;
		}

		for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
		{
			if( (dwRight&m_dwRightMask[i]) || (i==0&&dwRight<0x10000000) )
				m_dwRight[i] = dwRight&MASK_CHI_HU_RIGHT;
			else m_dwRight[i] = dwOtherRight;
		}

		return *this;
	}

	//�����
	CChiHuRight & CChiHuRight::operator &= ( dword dwRight )
	{
		bool bNavigate = false;
		//��֤Ȩλ
		if( !IsValidRight( dwRight ) )
		{
			//��֤ȡ��Ȩλ
			ASSERT( IsValidRight( ~dwRight ) );
			if( !IsValidRight( ~dwRight ) ) return *this;
			//����Ȩλ
			dword dwHeadRight = (~dwRight)&0xF0000000;
			dword dwTailRight = dwRight&MASK_CHI_HU_RIGHT;
			dwRight = dwHeadRight|dwTailRight;
			bNavigate = true;
		}

		for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
		{
			if( (dwRight&m_dwRightMask[i]) || (i==0&&dwRight<0x10000000) )
			{
				m_dwRight[i] &= (dwRight&MASK_CHI_HU_RIGHT);
			}
			else if( !bNavigate )
				m_dwRight[i] = 0;
		}

		return *this;
	}

	//�����
	CChiHuRight & CChiHuRight::operator |= ( dword dwRight )
	{
		//��֤Ȩλ
		if( !IsValidRight( dwRight ) ) return *this;

		for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
		{
			if( (dwRight&m_dwRightMask[i]) || (i==0&&dwRight<0x10000000) )
				m_dwRight[i] |= (dwRight&MASK_CHI_HU_RIGHT);
		}

		return *this;
	}

	//��
	CChiHuRight CChiHuRight::operator & ( dword dwRight )
	{
		CChiHuRight chr = *this;
		return (chr &= dwRight);
	}

	//��
	CChiHuRight CChiHuRight::operator & ( dword dwRight ) const
	{
		CChiHuRight chr = *this;
		return (chr &= dwRight);
	}

	//��
	CChiHuRight CChiHuRight::operator | ( dword dwRight )
	{
		CChiHuRight chr = *this;
		return chr |= dwRight;
	}

	//��
	CChiHuRight CChiHuRight::operator | ( dword dwRight ) const
	{
		CChiHuRight chr = *this;
		return chr |= dwRight;
	}

	//�Ƿ�ȨλΪ��
	bool CChiHuRight::IsEmpty()
	{
		for( BYTE i = 0; i < CountArray(m_dwRight); i++ )
			if( m_dwRight[i] ) return false;
		return true;
	}

	//����ȨλΪ��
	void CChiHuRight::SetEmpty()
	{
		zeromemory( m_dwRight,sizeof(m_dwRight) );
		return;
	}

	//��ȡȨλ��ֵ
	BYTE CChiHuRight::GetRightData( dword dwRight[], BYTE cbMaxCount )
	{
		ASSERT( cbMaxCount >= CountArray(m_dwRight) );
		if( cbMaxCount < CountArray(m_dwRight) ) return 0;

		memcpy( dwRight,m_dwRight,sizeof(dword)*CountArray(m_dwRight) );
		return CountArray(m_dwRight);
	}

	//����Ȩλ��ֵ
	bool CChiHuRight::SetRightData( const dword dwRight[], BYTE cbRightCount )
	{
		ASSERT( cbRightCount <= CountArray(m_dwRight) );
		if( cbRightCount > CountArray(m_dwRight) ) return false;

		zeromemory( m_dwRight,sizeof(m_dwRight) );
		memcpy( m_dwRight,dwRight,sizeof(dword)*cbRightCount );

		return true;
	}

	//����λ�Ƿ���ȷ
	bool CChiHuRight::IsValidRight( dword dwRight )
	{
		dword dwRightHead = dwRight & 0xF0000000;
		for( BYTE i = 0; i < CountArray(m_dwRightMask); i++ )
			if( m_dwRightMask[i] == dwRightHead ) return true;
		return false;
	}

	//////////////////////////////////////////////////////////////////////////



	//////////////////////////////////////////////////////////////////////////
	//��̬����

	//�˿�����
	const BYTE CGameLogic::m_cbCardDataArray[MAX_REPERTORY]=
	{
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
		0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,						//����
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
		0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,						//����
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
		0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,						//ͬ��
	};

	//////////////////////////////////////////////////////////////////////////

	//���캯��
	CGameLogic::CGameLogic()
	{
		m_cbMagicIndex = MAX_INDEX;
	}

	//��������
	CGameLogic::~CGameLogic()
	{
	}

	//�����˿�
	void CGameLogic::RandCardData(BYTE cbCardData[], BYTE cbMaxCount)
	{
		//����׼��
		BYTE cbCardDataTemp[CountArray(m_cbCardDataArray)];
		memcpy(cbCardDataTemp,m_cbCardDataArray,sizeof(m_cbCardDataArray));

		//�����˿�
		BYTE cbRandCount=0,cbPosition=0;
		do
		{
			cbPosition=rand()%(cbMaxCount-cbRandCount);
			cbCardData[cbRandCount++]=cbCardDataTemp[cbPosition];
			cbCardDataTemp[cbPosition]=cbCardDataTemp[cbMaxCount-cbRandCount];
		} while (cbRandCount<cbMaxCount);

		return;
	}

	//ɾ���˿�
	bool CGameLogic::RemoveCard(BYTE cbCardIndex[MAX_INDEX], BYTE cbRemoveCard)
	{
		//Ч���˿�
		ASSERT(IsValidCard(cbRemoveCard));
		ASSERT(cbCardIndex[SwitchToCardIndex(cbRemoveCard)]>0);

		//ɾ���˿�
		BYTE cbRemoveIndex=SwitchToCardIndex(cbRemoveCard);
		if (cbCardIndex[cbRemoveIndex]>0)
		{
			cbCardIndex[cbRemoveIndex]--;
			return true;
		}

		//ʧ��Ч��
		ASSERT(FALSE);

		return false;
	}

	//ɾ���˿�
	bool CGameLogic::RemoveCard(BYTE cbCardIndex[MAX_INDEX], const BYTE cbRemoveCard[], BYTE cbRemoveCount)
	{
		//ɾ���˿�
		for (BYTE i=0;i<cbRemoveCount;i++)
		{
			//Ч���˿�
			ASSERT(IsValidCard(cbRemoveCard[i]));
			ASSERT(cbCardIndex[SwitchToCardIndex(cbRemoveCard[i])]>0);

			//ɾ���˿�
			BYTE cbRemoveIndex=SwitchToCardIndex(cbRemoveCard[i]);
			if (cbCardIndex[cbRemoveIndex]==0)
			{
				//�������
				ASSERT(FALSE);

				//��ԭɾ��
				for (BYTE j=0;j<i;j++) 
				{
					ASSERT(IsValidCard(cbRemoveCard[j]));
					cbCardIndex[SwitchToCardIndex(cbRemoveCard[j])]++;
				}

				return false;
			}
			else 
			{
				//ɾ���˿�
				--cbCardIndex[cbRemoveIndex];
			}
		}

		return true;
	}

	BYTE CGameLogic::RemoveValueCardAll(BYTE cbCardData[], BYTE cbCardCount,BYTE cbRemoveCard)
	{

		BYTE cbCardIndex[MAX_INDEX];			//�����˿�
		SwitchToCardIndex(cbCardData,cbCardCount,cbCardIndex);
		BYTE cbRemoveCardArray[MAX_INDEX];
		BYTE cbRemoveCout = cbCardIndex[SwitchToCardIndex(cbRemoveCard)];
		for (int i = 0;i<cbRemoveCout;i++)
		{
			cbRemoveCardArray[i] = cbRemoveCard;
		}
		RemoveValueCard(cbCardData,cbCardCount,cbRemoveCardArray,cbRemoveCout);
		return cbCardCount - cbRemoveCout;
	}
	bool CGameLogic::RemoveValueCardOne(BYTE cbCardData[], BYTE cbCardCount,BYTE cbRemoveCard)
	{
		BYTE cbRemoveCardArray[MAX_INDEX];
		cbRemoveCardArray[0] = cbRemoveCard;
		return RemoveValueCard(cbCardData,cbCardCount,cbRemoveCardArray,1);
	}
	//ɾ���˿�
	bool CGameLogic::RemoveValueCard(BYTE cbCardData[], BYTE cbCardCount, const BYTE cbRemoveCard[], BYTE cbRemoveCount)
	{
		//��������
		ASSERT(cbCardCount<=14);
		ASSERT(cbRemoveCount<=cbCardCount);

		//�������
		BYTE cbDeleteCount=0,cbTempCardData[14];
		if (cbCardCount>CountArray(cbTempCardData))
			return false;
		memcpy(cbTempCardData,cbCardData,cbCardCount*sizeof(cbCardData[0]));

		//�����˿�
		for (BYTE i=0;i<cbRemoveCount;i++)
		{
			for (BYTE j=0;j<cbCardCount;j++)
			{
				if (cbRemoveCard[i]==cbTempCardData[j])
				{
					cbDeleteCount++;
					cbTempCardData[j]=0;
					break;
				}
			}
		}

		//�ɹ��ж�
		if (cbDeleteCount!=cbRemoveCount) 
		{
			ASSERT(FALSE);
			return false;
		}

		//�����˿�
		BYTE cbCardPos=0;
		for (BYTE i=0;i<cbCardCount;i++)
		{
			if (cbTempCardData[i]!=0) 
				cbCardData[cbCardPos++]=cbTempCardData[i];
		}

		return true;
	}

	//��Ч�ж�
	bool CGameLogic::IsValidCard(BYTE cbCardData)
	{
		BYTE cbValue=(cbCardData&MASK_VALUE);
		BYTE cbColor=(cbCardData&MASK_COLOR)>>4;
		return (((cbValue>=1)&&(cbValue<=9)&&(cbColor<=2))||((cbValue>=1)&&(cbValue<=7)&&(cbColor==3)));
	}

	//�˿���Ŀ
	BYTE CGameLogic::GetCardCount(const BYTE cbCardIndex[MAX_INDEX])
	{
		//��Ŀͳ��
		BYTE cbCardCount=0;
		for (BYTE i=0;i<MAX_INDEX;i++) 
			cbCardCount+=cbCardIndex[i];

		return cbCardCount;
	}

	//��ȡ���
	BYTE CGameLogic::GetWeaveCard(BYTE cbWeaveKind, BYTE cbCenterCard, BYTE cbCardBuffer[4])
	{
		//����˿�
		switch (cbWeaveKind)
		{
		case WIK_LEFT:		//���Ʋ���
			{
				//���ñ���
				cbCardBuffer[0]=cbCenterCard;
				cbCardBuffer[1]=cbCenterCard+1;
				cbCardBuffer[2]=cbCenterCard+2;

				return 3;
			}
		case WIK_RIGHT:		//���Ʋ���
			{
				//���ñ���
				cbCardBuffer[0]=cbCenterCard;
				cbCardBuffer[1]=cbCenterCard-1;
				cbCardBuffer[2]=cbCenterCard-2;

				return 3;
			}
		case WIK_CENTER:	//���Ʋ���
			{
				//���ñ���
				cbCardBuffer[0]=cbCenterCard;
				cbCardBuffer[1]=cbCenterCard-1;
				cbCardBuffer[2]=cbCenterCard+1;

				return 3;
			}
		case WIK_PENG:		//���Ʋ���
			{
				//���ñ���
				cbCardBuffer[0]=cbCenterCard;
				cbCardBuffer[1]=cbCenterCard;
				cbCardBuffer[2]=cbCenterCard;

				return 3;
			}
		case WIK_GANG:		//���Ʋ���
			{
				//���ñ���
				cbCardBuffer[0]=cbCenterCard;
				cbCardBuffer[1]=cbCenterCard;
				cbCardBuffer[2]=cbCenterCard;
				cbCardBuffer[3]=cbCenterCard;

				return 4;
			}
		default:
			{
				ASSERT(FALSE);
			}
		}

		return 0;
	}

	//�����ȼ�
	BYTE CGameLogic::GetUserActionRank(BYTE cbUserAction)
	{
		//���Ƶȼ�
		if (cbUserAction&WIK_CHI_HU) { return 4; }

		//���Ƶȼ�
		if (cbUserAction&WIK_GANG) { return 3; }

		//���Ƶȼ�
		if (cbUserAction&WIK_PENG) { return 2; }

		//���Ƶȼ�
		if (cbUserAction&(WIK_RIGHT|WIK_CENTER|WIK_LEFT)) { return 1; }

		return 0;
	}

	//���Ƶȼ�
	WORD CGameLogic::GetChiHuActionRank(const CChiHuRight & ChiHuRight)
	{
		WORD wFanShu = 0;
		return wFanShu;
	}

	//�����ж�
	BYTE CGameLogic::EstimateEatCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
	{
		//����Ч��
		ASSERT(IsValidCard(cbCurrentCard));

		//�����ж�
		if ( cbCurrentCard>=0x31 || IsMagicCard(cbCurrentCard) ) 
			return WIK_NULL;

		//��������
		BYTE cbExcursion[3]={0,1,2};
		BYTE cbItemKind[3]={WIK_LEFT,WIK_CENTER,WIK_RIGHT};

		//�����ж�
		BYTE cbEatKind=0,cbFirstIndex=0;
		BYTE cbCurrentIndex=SwitchToCardIndex(cbCurrentCard);
		for (BYTE i=0;i<CountArray(cbItemKind);i++)
		{
			BYTE cbValueIndex=cbCurrentIndex%9;
			if ((cbValueIndex>=cbExcursion[i])&&((cbValueIndex-cbExcursion[i])<=6))
			{
				//�����ж�
				cbFirstIndex=cbCurrentIndex-cbExcursion[i];

				//���Ʋ��ܰ���������
				if( m_cbMagicIndex != MAX_INDEX &&
					m_cbMagicIndex >= cbFirstIndex && m_cbMagicIndex <= cbFirstIndex+2 ) continue;

				if ((cbCurrentIndex!=cbFirstIndex)&&(cbCardIndex[cbFirstIndex]==0))
					continue;
				if ((cbCurrentIndex!=(cbFirstIndex+1))&&(cbCardIndex[cbFirstIndex+1]==0))
					continue;
				if ((cbCurrentIndex!=(cbFirstIndex+2))&&(cbCardIndex[cbFirstIndex+2]==0))
					continue;

				//��������
				cbEatKind|=cbItemKind[i];
			}
		}

		return cbEatKind;
	}

	//�����ж�
	BYTE CGameLogic::EstimatePengCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
	{
		//����Ч��
		ASSERT(IsValidCard(cbCurrentCard));

		//�����ж�
		if ( IsMagicCard(cbCurrentCard) ) 
			return WIK_NULL;

		//�����ж�
		return (cbCardIndex[SwitchToCardIndex(cbCurrentCard)]>=2)?WIK_PENG:WIK_NULL;
	}

	//�����ж�
	BYTE CGameLogic::EstimateGangCard(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCurrentCard)
	{
		//����Ч��
		ASSERT(IsValidCard(cbCurrentCard));

		//�����ж�
		if ( IsMagicCard(cbCurrentCard) ) 
			return WIK_NULL;

		//�����ж�
		return (cbCardIndex[SwitchToCardIndex(cbCurrentCard)]==3)?WIK_GANG:WIK_NULL;
	}

	//���Ʒ���
	BYTE CGameLogic::AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult)
	{
		//���ñ���
		BYTE cbActionMask=WIK_NULL;
		zeromemory(&GangCardResult,sizeof(GangCardResult));

		//���ϸ���
		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			if( i == m_cbMagicIndex ) continue;
			if (cbCardIndex[i]==4)
			{
				cbActionMask|=WIK_GANG;
				GangCardResult.cbCardData[GangCardResult.cbCardCount++]=SwitchToCardData(i);
			}
		}

		//��ϸ���
		for (BYTE i=0;i<cbWeaveCount;i++)
		{
			if (WeaveItem[i].cbWeaveKind==WIK_PENG)
			{
				if (cbCardIndex[SwitchToCardIndex(WeaveItem[i].cbCenterCard)]==1)
				{
					cbActionMask|=WIK_GANG;
					GangCardResult.cbCardData[GangCardResult.cbCardCount++]=WeaveItem[i].cbCenterCard;
				}
			}
		}

		return cbActionMask;
	}


	BYTE CGameLogic::AnalyseGangCard(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount, tagGangCardResult & GangCardResult)
	{
		//���ñ���
		BYTE cbActionMask=WIK_NULL;
		zeromemory(&GangCardResult,sizeof(GangCardResult));

		//���ϸ���
		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			if( i == m_cbMagicIndex ) continue;
			if (cbCardIndex[i]==4)
			{
				cbActionMask|=WIK_GANG;
				GangCardResult.cbCardData[GangCardResult.cbCardCount++]=SwitchToCardData(i);
			}
		}

		//��ϸ���
		for (BYTE i=0;i<cbWeaveCount;i++)
		{
			if (WeaveItem[i].cbWeaveKind==WIK_PENG)
			{
				if (cbCardIndex[SwitchToCardIndex(WeaveItem[i].cbCenterCard)]==1)
				{
					cbActionMask|=WIK_GANG;
					GangCardResult.cbCardData[GangCardResult.cbCardCount++]=WeaveItem[i].cbCenterCard;
				}
			}
		}

		return cbActionMask;
	}

	//�˿�ת��
	BYTE CGameLogic::SwitchToCardData(BYTE cbCardIndex)
	{
		ASSERT(cbCardIndex<34);
		return ((cbCardIndex/9)<<4)|(cbCardIndex%9+1);
	}

	//�˿�ת��
	BYTE CGameLogic::SwitchToCardIndex(BYTE cbCardData)
	{
		ASSERT(IsValidCard(cbCardData));
		return ((cbCardData&MASK_COLOR)>>4)*9+(cbCardData&MASK_VALUE)-1;
	}

	//�˿�ת��
	BYTE CGameLogic::SwitchToCardData(const BYTE cbCardIndex[MAX_INDEX], BYTE cbCardData[MAX_COUNT])
	{
		//ת���˿�
		BYTE cbPosition=0;
		//����
		if( m_cbMagicIndex != MAX_INDEX )
		{
			for( BYTE i = 0; i < cbCardIndex[m_cbMagicIndex]; i++ )
				cbCardData[cbPosition++] = SwitchToCardData(m_cbMagicIndex);
		}
		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			if( i == m_cbMagicIndex ) continue;
			if (cbCardIndex[i]!=0)
			{
				for (BYTE j=0;j<cbCardIndex[i];j++)
				{
					ASSERT(cbPosition<MAX_COUNT);
					cbCardData[cbPosition++]=SwitchToCardData(i);
				}
			}
		}

		return cbPosition;
	}

	//�˿�ת��
	BYTE CGameLogic::SwitchToCardIndex(const BYTE cbCardData[], BYTE cbCardCount, BYTE cbCardIndex[MAX_INDEX])
	{
		//���ñ���
		zeromemory(cbCardIndex,sizeof(BYTE)*MAX_INDEX);

		//ת���˿�
		for (BYTE i=0;i<cbCardCount;i++)
		{
			ASSERT(IsValidCard(cbCardData[i]));
			cbCardIndex[SwitchToCardIndex(cbCardData[i])]++;
		}

		return cbCardCount;
	}

	//����
	bool CGameLogic::IsMagicCard( BYTE cbCardData )
	{
		if( m_cbMagicIndex != MAX_INDEX )
			return SwitchToCardIndex(cbCardData) == m_cbMagicIndex;
		return false;
	}

	//����,������ֵ����
	bool CGameLogic::SortCardList( BYTE cbCardData[MAX_COUNT], BYTE cbCardCount )
	{
		//��Ŀ����
		if (cbCardCount==0||cbCardCount>MAX_COUNT) return false;

		//�������
		bool bSorted=true;
		BYTE cbSwitchData=0,cbLast=cbCardCount-1;
		do
		{
			bSorted=true;
			for (BYTE i=0;i<cbLast;i++)
			{
				int iTemp1 = cbCardData[i];
				int iTemp2 = cbCardData[i+1];
				if (iTemp1 > 0x30)
				{
					iTemp1 -= 0x40;
				}
				if (iTemp2 > 0x30)
				{
					iTemp2 -= 0x40;
				}
				if (iTemp1>iTemp2)
				{
					//���ñ�־
					bSorted=false;
					//�˿�����
					cbSwitchData=cbCardData[i];
					cbCardData[i]=cbCardData[i+1];
					cbCardData[i+1]=cbSwitchData;
				}	
			}
			cbLast--;
		} while(bSorted==false);

		return true;
	}

	/*
	// ������������
	*/

	//�����
	bool CGameLogic::IsPengPeng( const tagAnalyseItem *pAnalyseItem )
	{
		for( BYTE i = 0; i < CountArray(pAnalyseItem->cbWeaveKind); i++ )
		{
			if( pAnalyseItem->cbWeaveKind[i]&(WIK_LEFT|WIK_CENTER|WIK_RIGHT) )
				return false;
		}
		return true;
	}

	//��һɫ��
	bool CGameLogic::IsQingYiSe(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], const BYTE cbItemCount,const BYTE cbCurrentCard)
	{
		//�����ж�
		BYTE cbCardColor=0xFF;

		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			if(i==m_cbMagicIndex) continue;
			if (cbCardIndex[i]!=0)
			{
				//��ɫ�ж�
				if (cbCardColor!=0xFF)
					return false;

				//���û�ɫ
				cbCardColor=(SwitchToCardData(i)&MASK_COLOR);

				//��������
				i=(i/9+1)*9-1;
			}
		}

		//�������ֻ������
		if( cbCardColor == 0xFF )
		{
			ASSERT( m_cbMagicIndex != MAX_INDEX && cbCardIndex[m_cbMagicIndex] > 0 );
			//������
			ASSERT( cbItemCount > 0 );
			cbCardColor = WeaveItem[0].cbCenterCard&MASK_COLOR;
		}

		if((cbCurrentCard&MASK_COLOR)!=cbCardColor && !IsMagicCard(cbCurrentCard) ) return false;

		//����ж�
		for (BYTE i=0;i<cbItemCount;i++)
		{
			BYTE cbCenterCard=WeaveItem[i].cbCenterCard;
			if ((cbCenterCard&MASK_COLOR)!=cbCardColor)	return false;
		}

		return true;
	}

	//��С����
	bool CGameLogic::IsQiXiaoDui(const BYTE cbCardIndex[MAX_INDEX], const tagWeaveItem WeaveItem[], const BYTE cbWeaveCount,const BYTE cbCurrentCard)
	{
		//����ж�
		if (cbWeaveCount!=0) return false;

		//������Ŀ
		BYTE cbReplaceCount = 0;

		//��ʱ����
		BYTE cbCardIndexTemp[MAX_INDEX];
		memcpy(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));

		//��������
		BYTE cbCurrentIndex = SwitchToCardIndex(cbCurrentCard);
		cbCardIndexTemp[cbCurrentIndex]++;

		//���㵥��
		for (BYTE i=0;i<MAX_INDEX;i++)
		{
			BYTE cbCardCount=cbCardIndexTemp[i];

			//���ƹ���
			if( i == m_cbMagicIndex ) continue;

			//����ͳ��
			if( cbCardCount == 1 || cbCardCount == 3 ) 	cbReplaceCount++;
		}

		//���Ʋ���
		if( m_cbMagicIndex != MAX_INDEX && cbReplaceCount > cbCardIndexTemp[m_cbMagicIndex] ||
			m_cbMagicIndex == MAX_INDEX && cbReplaceCount > 0 )
			return false;

		return true;

	}

	//����
	bool CGameLogic::IsDaiYao( const tagAnalyseItem *pAnalyseItem )
	{
		//�������
		BYTE cbCardValue = pAnalyseItem->cbCardEye&MASK_VALUE;
		if( cbCardValue != 1 && cbCardValue != 9 ) return false;

		for( BYTE i = 0; i < CountArray(pAnalyseItem->cbWeaveKind); i++ )
		{
			if( pAnalyseItem->cbWeaveKind[i]&(WIK_LEFT|WIK_CENTER|WIK_RIGHT) )
			{
				BYTE j = 0;
				for(; j < 3; j++ )
				{
					cbCardValue = pAnalyseItem->cbCardData[i][j]&MASK_VALUE;
					if( cbCardValue == 1 || cbCardValue == 9 ) break;
				}
				if( j == 3 ) return false;
			}
			else
			{
				cbCardValue = pAnalyseItem->cbCenterCard[i]&MASK_VALUE;
				if( cbCardValue != 1 && cbCardValue != 9 ) return false;
			}
		}
		return true;
	}

	//����
	bool CGameLogic::IsJiangDui( const tagAnalyseItem *pAnalyseItem )
	{
		//�Ƿ�����
		if( !IsPengPeng(pAnalyseItem) ) return false;

		//�������
		BYTE cbCardValue = pAnalyseItem->cbCardEye&MASK_VALUE;
		if( cbCardValue != 2 && cbCardValue != 5 && cbCardValue != 8 ) return false;

		for( BYTE i = 0; i < CountArray(pAnalyseItem->cbWeaveKind); i++ )
		{
			if( pAnalyseItem->cbWeaveKind[i]&(WIK_LEFT|WIK_CENTER|WIK_RIGHT) )
			{
				BYTE j = 0;
				for(; j < 3; j++ )
				{
					cbCardValue = pAnalyseItem->cbCardData[i][j]&MASK_VALUE;
					if( cbCardValue == 2 || cbCardValue == 5 || cbCardValue == 8 ) break;
				}
				if( j == 3 ) return false;
			}
			else
			{
				cbCardValue = pAnalyseItem->cbCenterCard[i]&MASK_VALUE;
				if( cbCardValue != 2 && cbCardValue != 5 && cbCardValue != 8 ) return false;
			}
		}
		return true;
	}

	//�Ƿ���
	bool CGameLogic::IsHuaZhu( const BYTE cbCardIndex[], const tagWeaveItem WeaveItem[], BYTE cbWeaveCount )
	{
		BYTE cbColor[3] = { 0,0,0 };
		for( BYTE i = 0; i < MAX_INDEX; i++ )
		{
			if( cbCardIndex[i] > 0 )
			{
				BYTE cbCardColor = SwitchToCardData(i)&MASK_COLOR;
				cbColor[cbCardColor>>4]++;

				i = (i/9+1)*9-1;
			}
		}
		for( BYTE i = 0; i < cbWeaveCount; i++ )
		{
			BYTE cbCardColor = WeaveItem[i].cbCenterCard&MASK_COLOR;
			cbColor[cbCardColor>>4]++;
		}
		//ȱһ�žͲ��ǻ���
		for( BYTE i = 0; i < CountArray(cbColor); i++ )
			if( cbColor[i] == 0 ) return false;

		return true;
	}

	BYTE CGameLogic::GetCardColor(BYTE cbCardDat)
	{
		ASSERT(IsValidCard(cbCardDat));
		return ((cbCardDat&MASK_COLOR)>>4)+1;
	}

	BYTE CGameLogic::GetCardValue(BYTE cbCardDat)
	{
		ASSERT(IsValidCard(cbCardDat));
		return (cbCardDat&MASK_VALUE);
	}

	bool CGameLogic::AnalyseCard(const BYTE cbCardIndex[MAX_INDEX], const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount, AnalyseItemList & kAnalyseItemList)
	{
		//������Ŀ
		BYTE cbCardCount=GetCardCount(cbCardIndex);

		//Ч����Ŀ
		ASSERT((cbCardCount>=2)&&(cbCardCount<=MAX_COUNT)&&((cbCardCount-2)%3==0));
		if ((cbCardCount<2)||(cbCardCount>MAX_COUNT)||((cbCardCount-2)%3!=0))
			return false;

		//��������
		BYTE cbKindItemCount=0;
		tagKindItem KindItem[27*2+7+14];
		zeromemory(KindItem,sizeof(KindItem));

		//�����ж�
		BYTE cbLessKindItem=(cbCardCount-2)/3;
		ASSERT((cbLessKindItem+cbWeaveCount)==4);

		//�����ж�
		if (cbLessKindItem==0)
		{
			//Ч�����
			ASSERT((cbCardCount==2)&&(cbWeaveCount==4));
			//�����ж�
			for (BYTE i=0;i<MAX_INDEX;i++)
			{
				if (cbCardIndex[i]==2 || 
					( m_cbMagicIndex != MAX_INDEX && i != m_cbMagicIndex && cbCardIndex[m_cbMagicIndex]+cbCardIndex[i]==2 ) )
				{
					//��������
					tagAnalyseItem AnalyseItem;
					zeromemory(&AnalyseItem,sizeof(AnalyseItem));

					//���ý��
					for (BYTE j=0;j<cbWeaveCount;j++)
					{
						AnalyseItem.cbWeaveKind[j]=WeaveItem[j].cbWeaveKind;
						AnalyseItem.cbCenterCard[j]=WeaveItem[j].cbCenterCard;
						GetWeaveCard( WeaveItem[j].cbWeaveKind,WeaveItem[j].cbCenterCard,AnalyseItem.cbCardData[j] );
					}
					AnalyseItem.cbCardEye=SwitchToCardData(i);
					if( cbCardIndex[i] < 2 || i == m_cbMagicIndex )
						AnalyseItem.bMagicEye = true;
					else AnalyseItem.bMagicEye = false;

					if (cbCardIndex[m_cbMagicIndex] == 2)
					{
						AnalyseItem.bMagicEye = true;
						AnalyseItem.cbCardEye = SwitchToCardData(m_cbMagicIndex);
					}
					//������
					kAnalyseItemList.push_back(AnalyseItem);

					return true;
				}
			}

			return false;
		}

		//��ַ���
		BYTE cbMagicCardIndex[MAX_INDEX];
		memcpy(cbMagicCardIndex,cbCardIndex,sizeof(cbMagicCardIndex));
		BYTE cbMagicCardCount = 0;
		if( m_cbMagicIndex != MAX_INDEX )
		{
			cbMagicCardCount = cbCardIndex[m_cbMagicIndex];
			if( cbMagicCardIndex[m_cbMagicIndex] ) cbMagicCardIndex[m_cbMagicIndex] = 1;		//��С�������
		}
		if (cbCardCount>=3)
		{
			for (BYTE i=0;i<MAX_INDEX;i++)
			{
				//ͬ���ж�
				if (cbMagicCardIndex[i]+cbMagicCardCount>=3)
				{
					ASSERT( cbKindItemCount < CountArray(KindItem) );
					KindItem[cbKindItemCount].cbCardIndex[0]=i;
					KindItem[cbKindItemCount].cbCardIndex[1]=i;
					KindItem[cbKindItemCount].cbCardIndex[2]=i;
					KindItem[cbKindItemCount].cbWeaveKind=WIK_PENG;
					KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
					KindItem[cbKindItemCount].cbValidIndex[0] = cbMagicCardIndex[i]>0?i:m_cbMagicIndex;
					KindItem[cbKindItemCount].cbValidIndex[1] = cbMagicCardIndex[i]>1?i:m_cbMagicIndex;
					KindItem[cbKindItemCount].cbValidIndex[2] = cbMagicCardIndex[i]>2?i:m_cbMagicIndex;
					cbKindItemCount++;
					if(cbMagicCardIndex[i]+cbMagicCardCount>=6)
					{
						ASSERT( cbKindItemCount < CountArray(KindItem) );
						KindItem[cbKindItemCount].cbCardIndex[0]=i;
						KindItem[cbKindItemCount].cbCardIndex[1]=i;
						KindItem[cbKindItemCount].cbCardIndex[2]=i;
						KindItem[cbKindItemCount].cbWeaveKind=WIK_PENG;
						KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
						KindItem[cbKindItemCount].cbValidIndex[0] = cbMagicCardIndex[i]>3?i:m_cbMagicIndex;
						KindItem[cbKindItemCount].cbValidIndex[1] = m_cbMagicIndex;
						KindItem[cbKindItemCount].cbValidIndex[2] = m_cbMagicIndex;
						cbKindItemCount++;
					}
				}

				//�����ж�
				if ((i<(MAX_INDEX-9))&&((i%9)<7))
				{
					//ֻҪ������������3��˳���������������ڵ���3,��������

					if( cbMagicCardCount+cbMagicCardIndex[i]+cbMagicCardIndex[i+1]+cbMagicCardIndex[i+2] >= 3 )
					{
						BYTE cbIndex[3] = { i==m_cbMagicIndex?(BYTE)0:
							cbMagicCardIndex[i],(i+1)==m_cbMagicIndex?(BYTE)0:cbMagicCardIndex[i+1],
							(i+2)==m_cbMagicIndex?(BYTE)0:cbMagicCardIndex[i+2] };
						int nMagicCountTemp = cbMagicCardCount;
						BYTE cbValidIndex[3];
						while( nMagicCountTemp+cbIndex[0]+cbIndex[1]+cbIndex[2] >= 3 )
						{
							for( BYTE j = 0; j < CountArray(cbIndex); j++ )
							{
								if( cbIndex[j] > 0 ) 
								{
									cbIndex[j]--;
									cbValidIndex[j] = i+j;
								}
								else 
								{
									nMagicCountTemp--;
									cbValidIndex[j] = m_cbMagicIndex;
								}
							}
							if( nMagicCountTemp >= 0 )
							{
								ASSERT( cbKindItemCount < CountArray(KindItem) );
								KindItem[cbKindItemCount].cbCardIndex[0]=i;
								KindItem[cbKindItemCount].cbCardIndex[1]=i+1;
								KindItem[cbKindItemCount].cbCardIndex[2]=i+2;
								KindItem[cbKindItemCount].cbWeaveKind=WIK_LEFT;
								KindItem[cbKindItemCount].cbCenterCard=SwitchToCardData(i);
								memcpy( KindItem[cbKindItemCount].cbValidIndex,cbValidIndex,sizeof(cbValidIndex) );
								cbKindItemCount++;
							}
							else break;
						}
					}
				}
			}
		}

		//��Ϸ���
		if (cbKindItemCount>=cbLessKindItem)
		{
			//��������
			BYTE cbCardIndexTemp[MAX_INDEX];
			zeromemory(cbCardIndexTemp,sizeof(cbCardIndexTemp));

			//��������
			BYTE cbIndex[4]={0,1,2,3};
			tagKindItem pKindItem[4];
			zeromemory(pKindItem,sizeof(pKindItem));

			//��ʼ���
			do
			{
				//���ñ���
				memcpy(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));
				for (BYTE i=0;i<cbLessKindItem;i++)
					pKindItem[i]=KindItem[cbIndex[i]];

				//�����ж�
				bool bEnoughCard=true;
				for (BYTE i=0;i<cbLessKindItem*3;i++)
				{
					//�����ж�
					BYTE cbCardIndex=pKindItem[i/3].cbValidIndex[i%3]; 
					if (cbCardIndexTemp[cbCardIndex]==0)
					{	
						if( m_cbMagicIndex != MAX_INDEX && cbCardIndexTemp[m_cbMagicIndex] > 0 )
						{
							if (cbCardIndexTemp[m_cbMagicIndex] > 0)
							{
								cbCardIndexTemp[m_cbMagicIndex]--;
								pKindItem[i/3].cbValidIndex[i%3] = m_cbMagicIndex;
							}
						}
						else
						{
							bEnoughCard=false;
							break;
						}
					}
					else 
						cbCardIndexTemp[cbCardIndex]--;
				}

				//�����ж�
				if (bEnoughCard==true)
				{
					//�����ж�
					BYTE cbCardEye=0;
					bool bMagicEye = false;
					for (BYTE i=0;i<MAX_INDEX;i++)
					{
						if (cbCardIndexTemp[i]==2)
						{
							cbCardEye=SwitchToCardData(i);
							if( i == m_cbMagicIndex ) bMagicEye = true;
							break;
						}
						else if( i!=m_cbMagicIndex && 
							m_cbMagicIndex != MAX_INDEX && cbCardIndexTemp[i]+cbCardIndexTemp[m_cbMagicIndex]==2 )
						{
							cbCardEye = SwitchToCardData(i);
							bMagicEye = true;
						}
					}

					//�������
					if (cbCardEye!=0)
					{
						//��������
						tagAnalyseItem AnalyseItem;
						zeromemory(&AnalyseItem,sizeof(AnalyseItem));

						//�������
						for (BYTE i=0;i<cbWeaveCount;i++)
						{
							AnalyseItem.cbWeaveKind[i]=WeaveItem[i].cbWeaveKind;
							AnalyseItem.cbCenterCard[i]=WeaveItem[i].cbCenterCard;
							GetWeaveCard( WeaveItem[i].cbWeaveKind,WeaveItem[i].cbCenterCard,
								AnalyseItem.cbCardData[i] );
						}

						//��������
						for (BYTE i=0;i<cbLessKindItem;i++) 
						{
							AnalyseItem.cbWeaveKind[i+cbWeaveCount]=pKindItem[i].cbWeaveKind;
							AnalyseItem.cbCenterCard[i+cbWeaveCount]=pKindItem[i].cbCenterCard;
							for(int m = 0;m<3;m++)
							{
								AnalyseItem.cbCardData[cbWeaveCount+i][m] = SwitchToCardData(pKindItem[i].cbValidIndex[m]);
								if (pKindItem[i].cbValidIndex[m] == m_cbMagicIndex)
								{
									AnalyseItem.cbMagicIdex[pKindItem[i].cbCardIndex[m]] = 1;
								}
							}
						}

						//��������
						AnalyseItem.cbCardEye=cbCardEye;
						AnalyseItem.bMagicEye = bMagicEye;

						if (bMagicEye)
						{
							AnalyseItem.cbMagicIdex[SwitchToCardIndex(cbCardEye)] = 1;
						}
						//������
						kAnalyseItemList.push_back(AnalyseItem);
					}
				}

				//��������
				if (cbIndex[cbLessKindItem-1]==(cbKindItemCount-1))
				{
					BYTE i=cbLessKindItem-1;
					for (;i>0;i--)
					{
						if ((cbIndex[i-1]+1)!=cbIndex[i])
						{
							BYTE cbNewIndex=cbIndex[i-1];
							for (BYTE j=(i-1);j<cbLessKindItem;j++) 
								cbIndex[j]=cbNewIndex+j-i+2;
							break;
						}
					}
					if (i==0)
						break;
				}
				else
					cbIndex[cbLessKindItem-1]++;
			} while (true);

		}

		return kAnalyseItemList.size()>0;
	}

	void CGameLogic::getTingCardHZ(const BYTE cbCardIndex[MAX_INDEX],const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount,std::vector<BYTE>& kTingCardList)
	{
		BYTE cbMagicCard = 0x35;
		BYTE cbMagicIdex = SwitchToCardIndex(cbMagicCard);

		kTingCardList.clear();
		SYMJ::AnalyseItemList kAnalyseItemList;

		SYMJ::CGameLogic::Instance().SetMagicIndex(cbMagicIdex);
		//�����˿�
		BYTE cbCardIndexTemp[MAX_INDEX];
		memcpy(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));

		cbCardIndexTemp[cbMagicIdex]++;
		kAnalyseItemList.clear();
		BYTE   cbVaildCardIdex[MAX_INDEX];
		zeromemory(cbVaildCardIdex,sizeof(cbVaildCardIdex));
		bool bValue = SYMJ::CGameLogic::Instance().AnalyseCard(cbCardIndexTemp,WeaveItem,cbWeaveCount,kAnalyseItemList);
		for (int i = 0;i<kAnalyseItemList.size();i++)
		{
			tagAnalyseItem& kTemAnalyseItem = kAnalyseItemList[i];
			for (int m = 0;m<MAX_INDEX;m++)
			{
				if (kTemAnalyseItem.cbCardEye == cbMagicCard )
				{
					cbVaildCardIdex[m] = 1;
				}
				if (kTemAnalyseItem.cbMagicIdex[m])
				{
					cbVaildCardIdex[m] = 1;
				}

			}
		}

		for (int m = 0;m<MAX_INDEX-ZI_PAI_COUNT;m++)
		{
			if (cbVaildCardIdex[m])
			{
				kTingCardList.push_back(SwitchToCardData(m));;
			}
		}
		if ((int)kTingCardList.size()>0)
		{
			kTingCardList.push_back(cbMagicCard);;
		}
		cbCardIndexTemp[cbMagicIdex]--;
	}

	void CGameLogic::getTingCardSY(const BYTE cbCardIndex[MAX_INDEX],const CMD_WeaveItem WeaveItem[], BYTE cbWeaveCount,std::vector<BYTE>& kTingCardList)
	{
		kTingCardList.clear();
		SYMJ::AnalyseItemList kAnalyseItemList;
		//�����˿�
		BYTE cbCardIndexTemp[MAX_INDEX];
		memcpy(cbCardIndexTemp,cbCardIndex,sizeof(cbCardIndexTemp));

		for (int i=0;i<MAX_INDEX;i++)
		{
			cbCardIndexTemp[i]++;
			kAnalyseItemList.clear();
			bool bValue = SYMJ::CGameLogic::Instance().AnalyseCard(cbCardIndexTemp,WeaveItem,cbWeaveCount,kAnalyseItemList);
			if (bValue)
			{
				kTingCardList.push_back(SYMJ::CGameLogic::Instance().SwitchToCardData(i));
			}
			cbCardIndexTemp[i]--;
		}
	}

}

//////////////////////////////////////////////////////////////////////////