//-------------------------------------------------------------
//!
//! @brief �R���W����
//! @brief �Փˊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Collision
{
    //-------------------------------------------------------------
    //!
    //! @brief �X�y�[�X�f�B�r�W����
    //! @brief ��ԕ����֘A�̖��O���
    //!
    //-------------------------------------------------------------
    namespace SpaceDivision
    {
        //-------------------------------------------------------------
        //!
        //! @brief �N�A�b�h�c���[
        //! @brief 4���؊֘A�̖��O���
        //!
        //-------------------------------------------------------------
        namespace Quadtree
        {
            /*************************************************************//**
             *
             *  @brief  �R���X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            C_CollisionListCreater<T>::C_CollisionListCreater()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �f�X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            C_CollisionListCreater<T>::~C_CollisionListCreater()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �������������s��
             *  @param  �̈�̍��[
             *  @param  �̈�̏�[
             *  @param  �̈�̉E�[
             *  @param  �̈�̉��[
             *  @param  ��Ԃ̃��x��( 0����_ )
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::Initialize(float left,
                                                       float top,
                                                       float right,
                                                       float bottom,
                                                       uint32_t level)
            {
                // �ׂ��搔�l�z������߂�
                CalculateExponentialValue(level);

                // ���䋉���̘a���g���ċ�Ԑ������߂�
                cellNumber_ = (exponentialValues_[level + 1] - 1) / (4 - 1);

                // ���`��Ԃ𐶐����A������
                upCells_ = std::make_unique<std::unique_ptr<C_Cell<T>>[]>(cellNumber_);

                // ��Ԃ̃��x����ݒ�
                level_ = level;

                // �̈�̐ݒ�
                SetTerritory(left, top, right, bottom);
            }


            /*************************************************************//**
             *
             *  @brief  �c���[�̃I�u�W�F�N�g�̓o�^���s��
             *  @param  ���E�͈͂̍��[
             *  @param  ���E�͈͂̏�[
             *  @param  ���E�͈͂̉E�[
             *  @param  ���E�͈͂̉��[
             *  @param  �c���[�̃I�u�W�F�N�g
             *  @return ����I���Ftrue
             *  @return �ُ�I���Ffalse
             *
             ****************************************************************/
            template<typename T>
            bool C_CollisionListCreater<T>::Regist(float borderLeft,
                                                   float borderTop,
                                                   float borderRight,
                                                   float borderBottom,
                                                   S_TreeObject<T>* pTreeObject)
            {
                // ���E�͈͂���o�^���郂�[�g���ԍ����擾
                uint32_t mortonNumber = GetMortonNumberFromAABB(borderLeft,
                                                                borderTop,
                                                                borderRight,
                                                                borderBottom);

                // ��Ԃ��Ȃ��ꍇ�́A�V�����Z���𐶐�
                if (!upCells_[mortonNumber]) CreateCell(mortonNumber);

                // ��ԂɃI�u�W�F�N�g���v�b�V��
                return upCells_[mortonNumber]->Push(pTreeObject);
            }


            /*************************************************************//**
             *
             *  @brief  �Փ˔�����s���I�u�W�F�N�g�̃��X�g���擾����
             *  @param  �Փ˔�����s���I�u�W�F�N�g�̃y�A�̃��X�g
             *  @param  �Փˉ�( �v�f���̔��� )
             *  @return ����I���Ftrue
             *  @return �ُ�I���Ffalse
             *
             ****************************************************************/
            template<typename T>
            bool C_CollisionListCreater<T>::GetCollisionList(std::deque<T*>* ppCollisionPairList,
                                                             uint32_t* pCollisionCount)
            {
                // ���[�g��Ԃ�����Ă��邩�m�F
                if (!upCells_[0]) return false;

                // ���[�g��Ԃ̏Փ˔��胊�X�g���쐬
                std::deque<T*> pCollisionStack;
                CreateCollisionList(0, &pCollisionStack, ppCollisionPairList);
                assert(pCollisionStack.size() == 0);

                // �Փˉ񐔂��擾
                (*pCollisionCount) = ppCollisionPairList->size() / 2;

                return true;
            }


            /*************************************************************//**
             *
             *  @brief  �ׂ��搔�l�z����v�Z����
             *  @param  ��Ԃ̃��x��( 0����_ )
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::CalculateExponentialValue(uint32_t level)
            {
                // ���x����2�ǉ�( �z��̃T�C�Y�����킹�邽�� )
                level += 2;

                // �ׂ��搔�l�z��̗̈���m�ۂ��A�e���x���ł̋�Ԑ������߂�
                exponentialValues_.resize(level);

                exponentialValues_[0] = 1;

                for (size_t i = 1; i < level; ++i)
                {
                    exponentialValues_[i] = exponentialValues_[i - 1] * 4;
                }
            }


            /*************************************************************//**
             *
             *  @brief  �̈�̐ݒ���s��
             *  @param  �̈�̍��[
             *  @param  �̈�̏�[
             *  @param  �̈�̉E�[
             *  @param  �̈�̉��[
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::SetTerritory(float left,
                                                         float top,
                                                         float right,
                                                         float bottom)
            {
                // ���[�Ə�[��ݒ�
                left_ = left;
                top_ = top;

                // �̈�̕��ƍ�����ݒ�
                width_ = right - left;
                height_ = bottom - top;

                // �ŏ����x����Ԃ̕��ƍ�����ݒ�
                unitWidth_ = width_ / (1 << level_);
                unitHeight_ = height_ / (1 << level_);
            }


            /*************************************************************//**
             *
             *  @brief  ���E�͈͂��烂�[�g���ԍ��̎擾���s��
             *  @param  ���E�͈͂̍��[
             *  @param  ���E�͈͂̏�[
             *  @param  ���E�͈͂̉E�[
             *  @param  ���E�͈͂̉��[
             *  @return ���[�g���ԍ�
             *
             ****************************************************************/
            template<typename T>
            uint32_t C_CollisionListCreater<T>::GetMortonNumberFromAABB(float borderLeft,
                                                                        float borderTop,
                                                                        float borderRight,
                                                                        float borderBottom)
            {
                // ���E�͈͂̍���ƉE���̍��W�����[�g���ԍ��ɕϊ�
                uint32_t upperLeftMortonNumber = ConvertPointToMortonNumber(borderLeft, borderTop);
                uint32_t lowerRightMortonNumber = ConvertPointToMortonNumber(borderRight, borderBottom);

                // ����ƉE���̃��[�g���ԍ���r���I�_���a
                uint32_t exclusiveOrMortonNumber = upperLeftMortonNumber ^ lowerRightMortonNumber;

                // �ŏ�ʃ��x��
                uint32_t highestLevel = 0;

                for (uint32_t i = 0, check2Bit = 0; i < level_; ++i)
                {
                    // �r���I�_���a�̌��ʂ�2�i���ł̉���2bit�����Ɏ擾���A
                    // ���ꂪ0�ȊO�Ȃ�΍ŏ�ʃ��x���Ƃ��ĕێ�
                    check2Bit = (exclusiveOrMortonNumber >> (i * 2)) & 0x3;
                    if (check2Bit != 0) highestLevel = i + 1;
                }

                // ������Ԕԍ�������̃��[�g���ԍ����ŏ�ʃ��x����2�{���V�t�g���ċ��߂�
                uint32_t belongCellNumber = upperLeftMortonNumber >> (highestLevel * 2);

                // ���䋉���̘a����A������Ԕԍ��ɒǉ�����l( �ŏ��̗v�f�̐� )�����߁A�ǉ�
                uint32_t belongAddNumber = (exponentialValues_[level_ - static_cast<uint32_t>(highestLevel)] - 1) / (4 - 1);
                belongCellNumber += belongAddNumber;

                assert(belongCellNumber < cellNumber_);

                return belongCellNumber;
            }


            /*************************************************************//**
             *
             *  @brief  �_�����[�g���ԍ��֕ϊ�����
             *  @param  X���W
             *  @param  Y���W
             *  @return ���[�g���ԍ�
             *
             ****************************************************************/
            template<typename T>
            uint32_t C_CollisionListCreater<T>::ConvertPointToMortonNumber(float positionX, float positionY)
            {
                assert(positionX - left_ >= 0);
                assert(positionY - top_ >= 0);

                // �ŏ����x����Ԃ̕��ƍ����Ŋ������Z�����̍��W�𐮐��l�ŋ��߂�
                uint32_t unitCellPositionX = static_cast<uint32_t>((positionX - left_) / unitWidth_);
                uint32_t unitCellPositionY = static_cast<uint32_t>((positionY - top_) / unitHeight_);

                return BitSeparate32(unitCellPositionX) | BitSeparate32(unitCellPositionY) << 1;
            }


            /*************************************************************//**
             *
             *  @brief  1bit��т�32�r�b�g�ɕ�������
             *  @param  �l
             *  @return 1bit��т�32�r�b�g�ɕ��������l
             *
             ****************************************************************/
            template<typename T>
            uint32_t C_CollisionListCreater<T>::BitSeparate32(uint32_t value)
            {
                value = (value | (value << 8)) & 0x00ff00ff;
                value = (value | (value << 4)) & 0x0f0f0f0f;
                value = (value | (value << 2)) & 0x33333333;
                value = (value | (value << 1)) & 0x55555555;

                return value;
            }


            /*************************************************************//**
             *
             *  @brief  ��Ԃ��쐬����
             *  @param  �z��̗v�f
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::CreateCell(uint32_t element)
            {
                while (!upCells_[element])
                {
                    // �w��̗v�f�ԍ��ɋ�Ԃ�V�K�쐬
                    upCells_[element] = std::make_unique<C_Cell<T>>();

                    // �e��ԂɃW�����v
                    element = (element - 1) >> 2;

                    // �v�f���Z���̐��ȏ�ɂȂ������_�Ń��[�v�𔲂���
                    if (element >= cellNumber_) break;
                }
            }


            /*************************************************************//**
             *
             *  @brief  �Փ˔�����s���I�u�W�F�N�g�̃��X�g���쐬����
             *  @param  �Z���̗v�f
             *  @param  �Փ˔�����s���I�u�W�F�N�g�̃X�^�b�N
             *  @param  �Փ˔�����s���I�u�W�F�N�g�̃y�A�̃��X�g
             *  @return �Ȃ�
             *
             ****************************************************************/
            template<typename T>
            void C_CollisionListCreater<T>::CreateCollisionList(uint32_t cellElement,
                                                                std::deque<T*>* ppCollisionStack,
                                                                std::deque<T*>* ppCollisionPairList)
            {
                // �Ō�ɓo�^�����c���[�̃I�u�W�F�N�g���擾
                S_TreeObject<T>* pTreeObject = upCells_[cellElement]->GetLastTreeObject();

                while (pTreeObject)
                {
                    // �Ō�ɓo�^�������̃c���[�̃I�u�W�F�N�g���擾
                    S_TreeObject<T>* pAnotherTreeObject = pTreeObject->pNextObject_;

                    // ����ԓ��̃I�u�W�F�N�g���m�̏Փ˔��胊�X�g���쐬
                    while (pAnotherTreeObject)
                    {
                        (*ppCollisionPairList).push_back(pTreeObject->pObject_);
                        (*ppCollisionPairList).push_back(pAnotherTreeObject->pObject_);

                        // �����N���Ă��鎟�̃I�u�W�F�N�g�֐؂�ւ�
                        pAnotherTreeObject = pAnotherTreeObject->pNextObject_;
                    }

                    // �Փ˔�����s���I�u�W�F�N�g�̃X�^�b�N�Ƃ̏Փ˔��胊�X�g���쐬
                    for (auto& pCollisionObject : (*ppCollisionStack))
                    {
                        (*ppCollisionPairList).push_back(pTreeObject->pObject_);
                        (*ppCollisionPairList).push_back(pCollisionObject);
                    }

                    // �����N���Ă��鎟�̃I�u�W�F�N�g�֐؂�ւ�
                    pTreeObject = pTreeObject->pNextObject_;
                }

                // �q��Ԃ����݂��邩���f����t���O
                bool childCellFlag = false;

                // �I�u�W�F�N�g�̃J�E���^
                uint32_t objectCount = 0;

                for (size_t i = 0, nextElement = 0; i < 4; ++i)
                {
                    // ���ʒT�����邽�߂̎��̗v�f���v�Z
                    nextElement = cellElement * 4 + 1 + i;

                    if ((nextElement < cellNumber_) && (upCells_[nextElement]))
                    {
                        if (childCellFlag == false)
                        {
                            // �o�^����Ă���I�u�W�F�N�g���X�^�b�N�ɒǉ�
                            pTreeObject = upCells_[cellElement]->GetLastTreeObject();

                            while (pTreeObject)
                            {
                                ppCollisionStack->push_back(pTreeObject->pObject_);
                                pTreeObject = pTreeObject->pNextObject_;

                                // �J�E���^��1����
                                ++objectCount;
                            }

                            // �t���O�𗧂Ă�
                            childCellFlag = true;
                        }

                        // �q��Ԃœ����������s��
                        CreateCollisionList(nextElement, ppCollisionStack, ppCollisionPairList);
                    }
                }

                // �q��Ԃ��ł��Ă���ꍇ�A�X�^�b�N����I�u�W�F�N�g���O��
                if (childCellFlag == true) for (size_t i = 0; i < objectCount; ++i) ppCollisionStack->pop_back();
            }
        }
    }
}