/* ��d�C���N���[�h�h�~ */
#pragma once


/* �}�N����` */
#define JSON_ENABLE_INSERT_TAB 


/* �w�b�_�t�@�C�� */
#include "JsonDefine.h"


//-------------------------------------------------------------
///
/// @brief JSON
/// @brief JSON�֘A�̃N���X��֐��Ȃǂɕt���閼�O���
///
//-------------------------------------------------------------
namespace JSON
{
    //-------------------------------------------------------------
    //!
    //! @brief JSON�I�u�W�F�N�g
    //! @brief JSON�̃f�[�^���������߂̃N���X
    //!
    //-------------------------------------------------------------
    template <template<typename T>class Allocator = std::allocator, 
              typename AllocateObject = S_DefaultAlloc,
              typename FreeObject = S_DefaultFree>
    class C_JsonObject
    {
    public:

#pragma region �ʖ�
    
        using JsonObject = C_JsonObject<Allocator, AllocateObject, FreeObject>;             // JsonObject�^
        using Character = char;                                                             // Character�^
        using Integer = int32_t;                                                            // Integer�^
        using Real = double;                                                                // Real�^
        using Boolean = bool;                                                               // Boolean�^
        using String = std::basic_string<char, std::char_traits<char>, Allocator<char>>;    // String�^
        using Array = std::vector<JsonObject, Allocator<JsonObject>>;                       // Array�^
        using Object = std::unordered_map<String,                                           // Object�^
                                          JsonObject,
                                          std::hash<String>,
                                          std::equal_to<String>,
                                          Allocator<std::pair<String, JsonObject>>>;

#pragma endregion

    private:

#pragma region �^�C�v�T�C�Y�\����

        //-------------------------------------------------------------
        //!
        //! @brief �^�C�v�T�C�Y
        //! @brief �e��ނ̃T�C�Y��\���\����
        //!
        //-------------------------------------------------------------
        template<ecDataType dataType>
        struct S_TypeSize
        {
            static const std::size_t s_size = 0;                                            ///< @brief �^�̃T�C�Y
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_INTEGER>
        {
            static const std::size_t s_size = sizeof(Integer);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_REAL>
        {
            static const std::size_t s_size = sizeof(Real);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_BOOLEAN>
        {
            static const std::size_t s_size = sizeof(Boolean);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_STRING>
        {
            static const std::size_t s_size = sizeof(String);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_ARRAY>
        {
            static const std::size_t s_size = sizeof(Array);
        };

        template<>
        struct S_TypeSize<ecDataType::TYPE_OBJECT>
        {
            static const std::size_t s_size = sizeof(Object);
        };

#pragma endregion

#pragma region �R���e�i����N���X

        //-------------------------------------------------------------
        //!
        //! @brief �A�����C�I�y���[�V����
        //! @brief �z�񑀍���s�����߂̃N���X
        //!
        //-------------------------------------------------------------
        class C_ArrayOperation
        {
        public:
            /*************************************************************//**
             *
             *  @brief  �R���X�g���N�^
             *  @param  Json�I�u�W�F�N�g
             *
             ****************************************************************/
            C_ArrayOperation(JsonObject* pJsonObject) :

                // Json�I�u�W�F�N�g
                pJsonObject_(pJsonObject)

            {
            }


            /*************************************************************//**
             *
             *  @brief  �f�X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            ~C_ArrayOperation()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �v�f�̒ǉ����s��
             *  @param  �Ȃ�
             *  @return �Ȃ�
             *
             ****************************************************************/
            void Add()
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                rArray.emplace_back();
            }

            /*************************************************************//**
             *
             *  @brief  �v�f�̍폜���s��
             *  @param  �Ȃ�
             *  @return �Ȃ�
             *
             ****************************************************************/
            void Erase(Integer index)
            {
                auto& rArray = *pJsonObject_->ArrayCast();

                if (rArray.size() > index)
                {
                    auto iterator = rArray.begin() + index;
                    rArray.erase(iterator);
                }
            }


            /*************************************************************//**
             *
             *  @brief  �������̊m�ۂ��s��
             *  @param  �������T�C�Y
             *  @return �Ȃ�
             *
             ****************************************************************/
            void Reserve(Integer size)
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                rArray.reserve(size);
            }


            /*************************************************************//**
             *
             *  @brief  �v�f�����擾����
             *  @param  �Ȃ�
             *  @return �Ȃ�
             *
             ****************************************************************/
            std::size_t GetSize() const
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                return rArray.size();
            }


            /*************************************************************//**
             *
             *  @brief  �v�f�����擾����
             *  @param  �Ȃ�
             *  @return �Ȃ�
             *
             ****************************************************************/
            std::size_t GetCapacity() const
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                return rArray.capacity();
            }


            /*************************************************************//**
             *
             *  @brief  �Y�������Z�q�̃I�[�o�[���[�h
             *  @param  �C���f�b�N�X
             *  @return �Ȃ�
             *
             ****************************************************************/
            JsonObject& operator[](std::size_t index)
            {
                auto pJsonObject = GetJsonObject(index);

                while (pJsonObject == nullptr)
                {
                    std::size_t capacity = GetCapacity();
                    if (capacity < index) Reserve(capacity + 16);
                    
                    Add();
                    pJsonObject = GetJsonObject(index);
                }

                return *pJsonObject;
            }
        private:
            JsonObject* pJsonObject_ = nullptr;                                             ///< @brief Json�I�u�W�F�N�g

            /*************************************************************//**
             *
             *  @brief  Json�I�u�W�F�N�g���擾����
             *  @param  �Ȃ�
             *  @return �Ȃ�
             *
             ****************************************************************/
            JsonObject* GetJsonObject(std::size_t index)
            {
                auto& rArray = *pJsonObject_->ArrayCast();
                if (index < rArray.size()) return &rArray[index];
                
                return nullptr;
            }
        };

        //-------------------------------------------------------------
        //!
        //! @brief �I�u�W�F�N�g�I�y���[�V����
        //! @brief �A�z�z�񑀍���s�����߂̃N���X
        //!
        //-------------------------------------------------------------
        class C_ObjectOperation
        {
        public:
            /*************************************************************//**
             *
             *  @brief  �R���X�g���N�^
             *  @param  JSON�I�u�W�F�N�g
             *
             ****************************************************************/
            C_ObjectOperation(JsonObject* pJsonObject) : 

                // Json�I�u�W�F�N�g
                pJsonObject_(pJsonObject)

            {
            }


            /*************************************************************//**
             *
             *  @brief  �f�X�g���N�^
             *  @param  �Ȃ�
             *
             ****************************************************************/
            ~C_ObjectOperation()
            {
            }


            /*************************************************************//**
             *
             *  @brief  �擪���w���C�e���[�^���擾����
             *  @param  �Ȃ�
             *  @return �擪���w���C�e���[�^
             *
             ****************************************************************/
            typename Object::iterator Begin()
            {
                return pJsonObject_->ObjectCast()->begin();
            }


            /*************************************************************//**
             *
             *  @brief  �������w���C�e���[�^���擾����
             *  @param  �Ȃ�
             *  @return �������w���C�e���[�^
             *
             ****************************************************************/
            typename Object::iterator End()
            {
                return pJsonObject_->ObjectCast()->end();
            }


            /*************************************************************//**
             *
             *  @brief  �L�[����JSON�I�u�W�F�N�g����������
             *  @param  �L�[
             *  @return JSON�I�u�W�F�N�g
             *
             ****************************************************************/
            JsonObject* Find(const String& rKey)
            {
                auto& rObject = *pJsonObject_->ObjectCast();

                auto iterator = rObject.find(rKey);
                if (iterator != rObject.end()) return &(iterator->second);

                return nullptr;
            }


            /*************************************************************//**
             *
             *  @brief  JSON�I�u�W�F�N�g��}������
             *  @param  �L�[
             *  @return Json�I�u�W�F�N�g
             *
             ****************************************************************/
            JsonObject* Insert(const String& rKey)
            {
                auto& rObject = *pJsonObject_->ObjectCast();
                auto iterator = rObject.emplace(rKey, JsonObject(rKey)).first;

                return &(iterator->second);
            }


            /*************************************************************//**
             *
             *  @brief  JSON�I�u�W�F�N�g����������
             *  @param  �L�[
             *  @return �Ȃ�
             *
             ****************************************************************/
            void Erase(const String& rKey)
            {
                auto rObject = pJsonObject_->ObjectCast();

                auto iterator = rObject.find(rKey);
                if (iterator != rObject.end()) rObject.erase(iterator);
            }
        private:
            JsonObject* pJsonObject_ = nullptr;                                             ///< @brief Json�I�u�W�F�N�g
        };

#pragma endregion

    public:

#pragma region public�����o�֐�

        /*************************************************************//**
         *
         *  @brief  �f�t�H���g�R���X�g���N�^
         *  @param  �Ȃ�
         *
         ****************************************************************/
        C_JsonObject() = default;


        /*************************************************************//**
         *
         *  @brief  �R���X�g���N�^
         *  @param  �L�[
         *
         ****************************************************************/
        C_JsonObject(const String& rKey) :
            
            // �L�[
            key_(rKey)

        {
        }


        /*************************************************************//**
         *
         *  @brief  �R�s�[�R���X�g���N�^
         *  @param  JSON�I�u�W�F�N�g
         *
         ****************************************************************/
        C_JsonObject(const JsonObject& rOther) = delete;


        /*************************************************************//**
         *
         *  @brief  ���[�u�R���X�g���N�^
         *  @param  JSON�I�u�W�F�N�g
         *
         ****************************************************************/
		C_JsonObject(JsonObject&& rrOther)
        {
            *this = std::move(rrOther);
        }


        /*************************************************************//**
         *
         *  @brief  �f�X�g���N�^
         *  @param �Ȃ�
         *
         ****************************************************************/
        ~C_JsonObject()
        {
            DataFree();
        }


        /*************************************************************//**
         *
         *  @brief  �z�񑀍�̃I�u�W�F�N�g���擾����
         *  @param  �Ȃ�
         *  @return �z�񑀍�̃I�u�W�F�N�g
         *
         ****************************************************************/
        C_ArrayOperation GetArrayOperation()
        {
            return C_ArrayOperation(this);
        }


        /*************************************************************//**
         *
         *  @brief  �A�z�z�񑀍�̃I�u�W�F�N�g���擾����
         *  @param  �Ȃ�
         *  @return �A�z�z�񑀍�̃I�u�W�F�N�g
         *
         ****************************************************************/
        C_ObjectOperation GetObjectOperation()
        {
            return C_ObjectOperation(this);
        }


        /*************************************************************//**
         *
         *  @brief  �L�[���擾
         *  @param  �Ȃ�
         *  @return �L�[
         *
         ****************************************************************/
        const String& GetKey() const
        {
            return key_;
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾
         *  @param  �Ȃ�
         *  @return �l
         *
         ****************************************************************/
        template<typename T>
        T GetValue() const
        {
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾
         *  @param  �Ȃ�
         *  @return ����
         *
         ****************************************************************/
        template<>
        Integer GetValue<Integer>() const
        {
            return *IntegerCast();
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾
         *  @param  �Ȃ�
         *  @return ����
         *
         ****************************************************************/
        template<>
        Real GetValue<Real>() const
        {
            return *RealCast();
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾
         *  @param  �Ȃ�
         *  @return bool�l
         *
         ****************************************************************/
        template<>
        Boolean GetValue<Boolean>() const
        {
            return *BooleanCast();
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾
         *  @param  �Ȃ�
         *  @return ������
         *
         ****************************************************************/
        template<>
        String GetValue<String>() const
        {
            return *StringCast();
        }


        /*************************************************************//**
         *
         *  @brief  �l���擾
         *  @param  �Ȃ�
         *  @return ������
         *
         ****************************************************************/
        const char* GetTypeName() const
        {
            return GetTypeName(dataType_);
        }


        /*************************************************************//**
         *
         *  @brief  �z��Ƃ��č�蒼��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void RemakeAsArray()
        {
            if (DataAlloc<ecDataType::TYPE_ARRAY>() == true) Construct<Array>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  �A�z�z��Ƃ��č�蒼��
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void RemakeAsObject()
        {
            if (DataAlloc<ecDataType::TYPE_OBJECT>() == true) Construct<Object>(pValue_);
        }

#pragma endregion

#pragma region public�ÓI�����o�֐�

        /*************************************************************//**
         *
         *  @brief  �����񂩂�JSON�I�u�W�F�N�g���쐬����
         *  @param  ������
         *  @return JSON�I�u�W�F�N�g
         *
         ****************************************************************/
        static JsonObject s_CreateFromString(const String& rString)
        {
            // ������̒����ƃ������̃T�C�Y
            int32_t stringLength = rString.length();
            int32_t memorySize = stringLength + 1;

            // ���������蓖�ăI�u�W�F�N�g
            AllocateObject allocateObject;

            // ��������R�s�[
            std::unique_ptr<char, FreeObject> upCopyString(reinterpret_cast<char*>(allocateObject(memorySize)));
            std::memcpy(upCopyString.get(), rString.c_str(), memorySize);

            // �A�z�z�񂩂珇�ɉ��
            JsonObject object;
            s_ParseObject(&object, upCopyString.get());
        
            return object;
        }


        /*************************************************************//**
         *
         *  @brief  �t�@�C������JSON�I�u�W�F�N�g���쐬����
         *  @param  �t�@�C���p�X
         *  @return JSON�I�u�W�F�N�g
         *
         ****************************************************************/
        static JsonObject s_CreateFromFile(const String& rFilePath)
        {
            // �t�@�C�����J��
            std::ifstream inFile(rFilePath, std::ios::binary);

            if (inFile.fail() == true)
            {
                throw std::runtime_error("[ C_JsonObject::s_CreateFromFile ] : ���̓t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // �J�n�ƏI���̃C�e���[�^���X�g���[�����琶��
            std::istreambuf_iterator<char> beginIterator(inFile);
            std::istreambuf_iterator<char> lastIterator;

            // �t�@�C�����ۂ��ƕ�����Ƃ��ēǂݍ���
            String string(beginIterator, lastIterator);

            // �����񂩂�JSON�I�u�W�F�N�g���쐬
            return s_CreateFromString(string);
        }


        /*************************************************************//**
         *
         *  @brief  JSON�t�@�C�����������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �t�@�C���p�X
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteToJsonFile(const JsonObject& rJsonObject, const String& rFilePath)
        {
            // �t�@�C�����J��
            std::ofstream outFile(rFilePath);

            if (outFile.fail() == true)
            {
                throw std::runtime_error("[ C_JsonObject::s_WriteToJsonFile ] : �o�̓t�@�C�����J���̂Ɏ��s���܂����B");
            }

            // ��ޕʂɏ�������
            s_WriteTypeDistinguish(rJsonObject, &outFile);
        }

#pragma endregion

#pragma region public���Z�q�̃I�[�o�[���[�h
        
        /*************************************************************//**
         *
         *  @brief  ������Z�q�̃I�[�o�[���[�h
         *  @param  JSON�I�u�W�F�N�g
         *  @return �Ȃ�
         *
         ****************************************************************/
        void operator=(const JsonObject& rOther) = delete;


        /*************************************************************//**
         *
         *  @brief  ������Z�q�̃I�[�o�[���[�h( ���[�u )
         *  @param  JSON�I�u�W�F�N�g
         *  @return �Ȃ�
         *
         ****************************************************************/
        void operator=(JsonObject&& rrOther)
        {
            // �l�����
            if (pValue_) DataFree();

            // �e�f�[�^��ݒ�
            key_ = rrOther.key_;
			pValue_ = rrOther.pValue_;
			dataType_ = rrOther.dataType_;
			rrOther.pValue_ = nullptr;
		}


        /*************************************************************//**
         *
         *  @brief  ������Z�q�̃I�[�o�[���[�h
         *  @param  ����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void operator=(Integer value)
        {
            DataAlloc<ecDataType::TYPE_INTEGER>();
            Assign(value);
        }


        /*************************************************************//**
         *
         *  @brief  ������Z�q�̃I�[�o�[���[�h
         *  @param  ����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void operator=(Real value)
        {
            DataAlloc<ecDataType::TYPE_REAL>();
            Assign(value);
        }


        /*************************************************************//**
         *
         *  @brief  ������Z�q�̃I�[�o�[���[�h
         *  @param  ������
         *  @return �Ȃ�
         *
         ****************************************************************/
        void operator=(const String& rString)
        {
            DataAlloc<ecDataType::TYPE_STRING>();
            Construct<String>(pValue_, rString);
        }


        /*************************************************************//**
         *
         *  @brief  ������Z�q�̃I�[�o�[���[�h
         *  @param  bool�l
         *  @return �Ȃ�
         *
         ****************************************************************/
        void operator=(Boolean value)
        {
            DataAlloc<ecDataType::TYPE_BOOLEAN>();
            Assign(value);
        }


        /*************************************************************//**
         *
         *  @brief  �Y�������Z�q�̃I�[�o�[���[�h
         *  @param  �C���f�b�N�X
         *  @return JSON�I�u�W�F�N�g
         *
         ****************************************************************/
        JsonObject& operator[](std::size_t index)
        {
            // �z�񑀍�̃I�u�W�F�N�g���擾
            C_ArrayOperation arrayOperation = GetArrayOperation();

            // ���������m��
            if (DataAlloc<ecDataType::TYPE_ARRAY>() == true)
            {
                Construct<Array>(pValue_);
                arrayOperation.Reserve(16);
            }

            return arrayOperation[index];
        }


        /*************************************************************//**
         *
         *  @brief  �Y�������Z�q�̃I�[�o�[���[�h
         *  @param  �L�[
         *  @return JSON�I�u�W�F�N�g
         *
         ****************************************************************/
        JsonObject& operator[](const String& rKey)
        {
            // �A�z�z�񑀍�̃I�u�W�F�N�g���擾
            C_ObjectOperation objectOperation = GetObjectOperation();
            
            // ���������m��
            if (DataAlloc<ecDataType::TYPE_OBJECT>() == true) Construct<Object>(pValue_);

            // �L�[����v�f���������A������Ȃ��ꍇ�͗v�f��}��
            JsonObject* pJsonObject = objectOperation.Find(rKey);
            if (pJsonObject == nullptr) pJsonObject = objectOperation.Insert(rKey);

            return *pJsonObject;
        }

#pragma endregion

    private:

#pragma region �����o�ϐ�

        void* pValue_ = nullptr;                                                            ///< @brief �l
        String key_;                                                                        ///< @brief �L�[
        ecDataType dataType_ = ecDataType::TYPE_NULL;                                       ///< @brief �f�[�^�̎��
        AllocateObject allocateObject_;                                                     ///< @brief ���������蓖�Ăɗp����I�u�W�F�N�g
        FreeObject freeObject_;                                                             ///< @brief ����������ɗp����I�u�W�F�N�g

#pragma endregion

#pragma region private�����o�֐�

        /*************************************************************//**
         *
         *  @brief  �w�肵����ނ̃��������m�ۂ���
         *  @param  �Ȃ�
         *  @return �m�ۂ����ꍇ      �Ftrue
         *  @return �m�ۂ���Ă����ꍇ�Ffalse
         *
         ****************************************************************/
        template<ecDataType dataType>
        bool DataAlloc()
        {
            // �^���s��v�̏ꍇ�A���������Ċm��
            if (TypeEqual(dataType) == false)
            {
                // ���������m��
                if (Alloc(S_TypeSize<dataType>::s_size) == false)
                {
                    DataFree();
                    Alloc(S_TypeSize<dataType>::s_size);
                }

                // �f�[�^�̎�ނ�ݒ�
                dataType_ = dataType;

                return true;
            }

            return false;
        }


        /*************************************************************//**
         *
         *  @brief  �T�C�Y���������������m�ۂ���
         *  @param  �������̃T�C�Y
         *  @return �m�ۂ����ꍇ      �Ftrue
         *  @return �m�ۂ���Ă����ꍇ�Ffalse
         *
         ****************************************************************/
        bool Alloc(std::size_t size)
        {
            if (pValue_ == nullptr)
            {
                pValue_ = allocateObject_(size);

                return true;
            }

            return false;
        }


        /*************************************************************//**
         *
         *  @brief  ���������m�ۂ���
         *  @param  �Ȃ�
         *  @return �Ȃ�
         *
         ****************************************************************/
        void DataFree()
        {
            // ������E�z��E�A�z�z��̏ꍇ�̓f�X�g���N�^���Ă�
            if (pValue_)
            {
                switch (dataType_)
                {
                case ecDataType::TYPE_STRING:

                    Destruct<String>(pValue_);

                    break;
                case ecDataType::TYPE_ARRAY:

                    Destruct<Array>(pValue_);

                    break;
                case ecDataType::TYPE_OBJECT:

                    Destruct<Object>(pValue_);

                    break;
                }

                // �����������
                freeObject_(pValue_);
                pValue_ = nullptr;
            }
        }


        /*************************************************************//**
         *
         *  @brief  �f�[�^�̎�ނ��r����
         *  @param  �f�[�^�̎��
         *  @return ��ނ�������ȊO�œ����ꍇ�Ftrue
         *  @return ��ނ��Ⴄ�ꍇ            �Ffalse
         *
         ****************************************************************/
        bool TypeEqual(ecDataType dataType)
        {
            if (dataType_ != ecDataType::TYPE_STRING && dataType_ == dataType) return true;

            return false;
        }


        /*************************************************************//**
         *
         *  @brief  ��ނ̖��O���擾����
         *  @param  �f�[�^�̎��
         *  @return ��ނ̖��O
         *
         ****************************************************************/
        const char* GetTypeName(ecDataType dataType)
        {
            switch (dataType_)
            {
            case ecDataType::TYPE_INTEGER:

                return "Integer";

                break;
            case ecDataType::TYPE_REAL:

                return "Real";

                break;
            case ecDataType::TYPE_BOOLEAN:

                return "Boolean";

                break;
            case ecDataType::TYPE_STRING:

                return "String";

                break;
            case ecDataType::TYPE_ARRAY:

                return "Array";

                break;
            case ecDataType::TYPE_OBJECT:

                return "Object";

                break;
            case ecDataType::TYPE_NULL:

                return "Null";

                break;
            }

            return "Unknown";
        }


        /*************************************************************//**
         *
         *  @brief  �l��������
         *  @param  ����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Assign(Integer value)
        {
            auto pIntegerValue = IntegerCast();
            *pIntegerValue = value;
        }


        /*************************************************************//**
         *
         *  @brief  �l��������
         *  @param  ����
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Assign(Real value)
        {
            auto pRealValue = RealCast();
            *pRealValue = value;
        }


        /*************************************************************//**
         *
         *  @brief  �l��������
         *  @param  �u�[���l
         *  @return �Ȃ�
         *
         ****************************************************************/
        void Assign(Boolean value)
        {
            auto pBooleanValue = BooleanCast();
            *pBooleanValue = value;
        }


        /*************************************************************//**
         *
         *  @brief  �����I�R���X�g���N�^�̌Ăяo�����s��
         *  @param  �|�C���^
         *  @param  ��������^�̈�����
         *  @return �Ȃ�
         *
         ****************************************************************/
        template<typename T, typename ...Args>
        void Construct(void* pPointer, Args&&... args)
        {
           ::new (pPointer)T(std::forward<Args>(args)...);
        }


        /*************************************************************//**
         *
         *  @brief  �����I�f�X�g���N�^�̌Ăяo�����s��
         *  @param  �|�C���^
         *  @return �Ȃ�
         *
         ****************************************************************/
        template<typename T>
        void Destruct(void* pPointer)
        {
            reinterpret_cast<T*>(pPointer)->~T();
        }


        /*************************************************************//**
         *
         *  @brief  Character�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return Character�^�̒l
         *
         ****************************************************************/
        Character* CharacterCast() const
        {
            return reinterpret_cast<Character*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Integer�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return Integer�^�̒l
         *
         ****************************************************************/
        Integer* IntegerCast() const
        {
            return reinterpret_cast<Integer*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Real�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return Real�^�̒l
         *
         ****************************************************************/
        Real* RealCast() const
        {
            return reinterpret_cast<Real*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Boolean�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return Boolean�^�̒l
         *
         ****************************************************************/
        Boolean* BooleanCast() const
        {
            return reinterpret_cast<Boolean*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  String�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return String�^�̒l
         *
         ****************************************************************/
        String* StringCast() const
        {
            return reinterpret_cast<String*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Array�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return Array�^�̒l
         *
         ****************************************************************/
        Array* ArrayCast() const
        {
            return reinterpret_cast<Array*>(pValue_);
        }


        /*************************************************************//**
         *
         *  @brief  Object�^�փL���X�g���s��
         *  @param  �Ȃ�
         *  @return Object�^�̒l
         *
         ****************************************************************/
        Object* ObjectCast() const
        {
            return reinterpret_cast<Object*>(pValue_);
        }

#pragma endregion

#pragma region private�ÓI�����o�֐�

        /*************************************************************//**
         *
         *  @brief  �A�z�z�����͂���
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static char* s_ParseObject(JsonObject* pJsonObject, char* pString)
        {
            // ���[�v�I���t���O
            bool loopFinishFlag = false;

            // ������( �J )�̏ꍇ�͕�������i�߁AJson�I�u�W�F�N�g���I�u�W�F�N�g�Ƃ��č\�z
            if (*pString == '{')
            {
                ++pString;
                pJsonObject->RemakeAsObject();
            }

            do
            {
                switch (*pString)
                {
                /* ������( �J ) */
                case '{':

                    // �ċA�I�ɉ�͂��s��
                    pString = s_ParseObject(pJsonObject, pString);

                    break;
                /* ������( �� ) */
                case '}':

                    ++pString;
                    loopFinishFlag = true;

                    break;
                /* �_�u���N�H�[�e�[�V����( �f�[�^ ) */
                case '\"':
                {
                    // �l�̖��O���擾
                    auto valueNameAndNextString = s_GetValueName(pString);

                    String valueName = std::get<0>(valueNameAndNextString);
                    pString = std::get<1>(valueNameAndNextString);

                    // �l�����蓖�Ă�
                    pString = s_AssignValue(&((*pJsonObject)[valueName]), pString);
                }
                    break;
                /* ���̑� */
                default:

                    ++pString;

                    break;
                }
            } while (loopFinishFlag == false);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  �l�̖��O���擾����
         *  @param  ������
         *  @return �l�̖��O�Ǝ��̕�����
         *
         ****************************************************************/
        static std::tuple<String, char*> s_GetValueName(char* pString)
        {
            // �����̃C���f�b�N�X
            int32_t stringIndex = 0;

            // 1�ڂ̃_�u���N�H�[�e�[�V�����̓C���f�b�N�X��1�i�߂�
            if (pString[stringIndex] == '\"') ++stringIndex;

            // �l�̖��O�ƕ����̐�
            char valueName[256] = {};
            int32_t characterCount = 0;

            // 2�ڂ̃_�u���N�H�[�e�[�V����������܂Œl�̖��O�Ƃ��ĕ������擾
            while (pString[stringIndex] != '\"')
            {
                valueName[characterCount] = pString[stringIndex];

                ++stringIndex;
                ++characterCount;
            }

            // �������ƕ������Ԃ�
            return std::make_tuple(String(valueName), pString + stringIndex + 1);
        }


        /*************************************************************//**
         *
         *  @brief  �l�̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return �l�̖��O�Ǝ��̕�����
         *
         ****************************************************************/
        static char* s_AssignValue(JsonObject* pJsonObject, char* pString)
        {
            // ���[�v�I���t���O
            bool loopFinishFlag = false;

            do
            {
                switch (*pString)
                {
                /* ������( �J ) */
                case '{':

                    pString = s_ParseObject(pJsonObject, pString);
                    loopFinishFlag = true;

                    break;
                /* ������( �� ) */
                case '}':

                    ++pString;
                    loopFinishFlag = true;

                    break;
                /* ������( �� ) */
                case '\"':

                    pString = s_AssignString(pJsonObject, pString);
                    loopFinishFlag = true;

                    break;
                /* �p����( �J ) */
                case '[':

                    pString = s_AssignArray(pJsonObject, pString);
                    loopFinishFlag = true;

                    break;
                /* ���̑� */
                default:
                {
                    // �����̊��蓖�Ă��s��
                    // ���蓖�Ă��Ȃ������ꍇ�͕�����1�i�߂ă��[�v
                    auto resultFlagAndNextString = s_AssignNumber(pJsonObject, pString);

                    if (std::get<0>(resultFlagAndNextString) == true)
                    {
                        pString = std::get<1>(resultFlagAndNextString);
                        loopFinishFlag = true;
                    }
                    else
                    {
                        ++pString;
                    }
                }
                    break;
                }

            } while (loopFinishFlag == false);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  �z��̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static char* s_AssignArray(JsonObject* pJsonObject, char* pString)
        {
            // �p����( �J )�̏ꍇ�͕�����1�i�߁AJSON�I�u�W�F�N�g��z��Ƃ��č\�z
            if (*pString == '[')
            {
                ++pString;
                pJsonObject->RemakeAsArray();
            }

            // JSON�I�u�W�F�N�g�̃C���f�b�N�X
            int32_t jsonObjectIndex = 0;

            // ���[�v�I���̃t���O
            bool loopFinishFlag = false;

            do
            {
                switch (*pString)
                {
                /* �p����( �J ) */
                case '[':

                    pString = s_AssignArray(&((*pJsonObject)[jsonObjectIndex]), pString);

                    break;
                /* �p����( �� ) */
                case ']':

                    ++pString;
                    loopFinishFlag = true;

                    break;
                /* �J���} */
                case ',':

                    ++jsonObjectIndex;
                    ++pString;

                    break;
                /* ������( �J ) */
                case '{':

                    pString = s_ParseObject(&((*pJsonObject)[jsonObjectIndex]), pString);

                    break;
                /* �_�u���N�H�[�e�[�V���� */
                case '\"':

                    pString = s_AssignString(&((*pJsonObject)[jsonObjectIndex]), pString);

                    break;
                /* ���̑� */
                default:
                {
                    // �����̊��蓖�Ă��s��
                    // ���蓖�Ă��Ȃ������ꍇ�͕�����1�i�߂ă��[�v
                    auto resultFlagAndString = s_AssignNumber(&((*pJsonObject)[jsonObjectIndex]), pString);

                    if (std::get<0>(resultFlagAndString) == true)
                    {
                        pString = std::get<1>(resultFlagAndString);
                    }
                    else
                    {
                        ++pString;
                    }
                }
                    break;
                }

            } while (loopFinishFlag == false);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  ������̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static char* s_AssignString(JsonObject* pJsonObject, char* pString)
        {
            auto valueNameAndNextString = s_GetValueName(pString);

            *pJsonObject = std::get<0>(valueNameAndNextString);
            pString = std::get<1>(valueNameAndNextString);

            return pString;
        }


        /*************************************************************//**
         *
         *  @brief  �����̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static std::tuple<bool, char*> s_AssignNumber(JsonObject* pJsonObject, char* pString)
        {
            bool resultFlag = false;

            /* ���l�̏ꍇ */
            if (*pString >= '0' && *pString <= '9')
            {
                pString = s_AssignIntegerOrReal(pJsonObject, pString);
                resultFlag = true;
            }
            /* bool�l�̏ꍇ */
            else if (*pString == 't' || *pString == 'f')
            {
                pString = s_AssignBoolean(pJsonObject, pString);
                resultFlag = true;
            }
            /* null�l�̏ꍇ */
            else if (*pString == 'n')
            {
                pString = s_AssignNull(pJsonObject, pString);
                resultFlag = true;
            }

            return std::make_tuple(resultFlag, pString);
        }


        /*************************************************************//**
         *
         *  @brief  �����܂��͎����̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static char* s_AssignIntegerOrReal(JsonObject* pJsonObject, char* pString)
        {
            // �l�̕�����
            char valueString[256] = {};
            
            // ���������f����t���O
            bool realFlag = false;

            // �l�̕�����̃C���f�b�N�X
            int valueStringIndex = 0;

            // �l�̕�������擾
            while (true)
            {
                if (pString[valueStringIndex] == ',' || pString[valueStringIndex] == '}' || pString[valueStringIndex] == ']')
                {
                    break;
                }
                else if ((pString[valueStringIndex] >= '0' && pString[valueStringIndex] <= '9') || pString[valueStringIndex] == '.')
                {
                    valueString[valueStringIndex] = pString[valueStringIndex];

                    if (pString[valueStringIndex] == '.') realFlag = true;
                }

                ++valueStringIndex;
            }

            // ������𐔒l��
            if (realFlag == true)
            {
                *pJsonObject = std::stod(valueString);
            }
            else
            {
                *pJsonObject = std::stoi(valueString);
            }
            
            return pString + valueStringIndex;
        }


        /*************************************************************//**
         *
         *  @brief  �u�[���l�̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static char* s_AssignBoolean(JsonObject* pJsonObject, char* pString)
        {
            // ������
            int32_t stringCount = 0;

            /* true�̏ꍇ */
            if (*pString == 't')
            {
                *pJsonObject = true;
                stringCount = 4;
            }
            /* false�̏ꍇ */
            else
            {
                *pJsonObject = false;
                stringCount = 5;
            }

            return pString + stringCount;
        }


        /*************************************************************//**
         *
         *  @brief  null�l�̊��蓖�Ă��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  ������
         *  @return ���̕�����
         *
         ****************************************************************/
        static char* s_AssignNull(JsonObject* pJsonObject, char* pString)
        {
            return pString + 4;
        }


        /*************************************************************//**
         *
         *  @brief  ��ޕʂɏ������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @param  �^�u�����ɑ}���ς݂����f����t���O
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteTypeDistinguish(const JsonObject& rJsonObject, std::ofstream* pOutFile, bool tabAlreadyInsertFlag = false)
        {
            switch (rJsonObject.dataType_)
            {
            case ecDataType::TYPE_INTEGER:

                s_WriteInteger(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_REAL:

                s_WriteReal(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_BOOLEAN:

                s_WriteBoolean(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_STRING:

                s_WriteString(rJsonObject, pOutFile);

                break;
            case ecDataType::TYPE_ARRAY:

                s_WriteArray(rJsonObject, pOutFile, tabAlreadyInsertFlag);

                break;
            case ecDataType::TYPE_OBJECT:

                s_WriteObject(rJsonObject, pOutFile, tabAlreadyInsertFlag);

                break;
            case ecDataType::TYPE_NULL:

                s_WriteNull(rJsonObject, pOutFile);

                break;
            }
        }


        /*************************************************************//**
         *
         *  @brief  �����̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteInteger(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";

            *pOutFile << rJsonObject.GetValue<Integer>();
        }


        /*************************************************************//**
         *
         *  @brief  �����̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteReal(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";
            
            *pOutFile << std::fixed << std::setprecision(6) << rJsonObject.GetValue<Real>();
        }


        /*************************************************************//**
         *
         *  @brief  bool�l�̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteBoolean(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";

            rJsonObject.GetValue<Boolean>() == true ? *pOutFile << "true" : *pOutFile << "false";
        }


        /*************************************************************//**
         *
         *  @brief  ������̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteString(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            String key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";
            

            *pOutFile << "\"" << rJsonObject.GetValue<String>() << "\"";
        }


        /*************************************************************//**
         *
         *  @brief  �z��̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @param  �^�u�����ɑ}���ς݂����f����t���O
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteArray(const JsonObject& rJsonObject, std::ofstream* pOutFile, bool tabAlreadyInsertFlag)
        {
            // �L�[���擾
            String key = rJsonObject.GetKey();

            // �L�[�Ɗp����( �J )����������
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : \n";
            if (tabAlreadyInsertFlag == false) s_WriteTab(pOutFile);
            *pOutFile << "[\n";

            // �z����擾
            auto& rArray = *rJsonObject.ArrayCast();

            // �z��̃C�e���[�^���擾
            auto iterator = rArray.begin();

            // ���[�v�̏I���𔻒f����t���O
            bool loopFinishFlag = !(iterator != rArray.end());

            // �^�u��1����
            s_WriteTab(nullptr, 1);

            while (loopFinishFlag == false)
            {
                // �^�u��}��
                s_WriteTab(pOutFile);

                // ��ޕʂɏ�������
                s_WriteTypeDistinguish(*iterator, pOutFile, true);
                ++iterator;

                // ���[�v�̏I���𔻒f
                if (iterator != rArray.end())
                {
                    *pOutFile << ",\n";
                }
                else
                {
                    loopFinishFlag = true;
                }
            }

            // �^�u��1����
            s_WriteTab(nullptr, -1);

            // ���s���p����( �� )����������
            *pOutFile << "\n";
            s_WriteTab(pOutFile);
            *pOutFile << "]";
        }


        /*************************************************************//**
         *
         *  @brief  �A�z�z��̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @param  �^�u�����ɑ}���ς݂����f����t���O
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteObject(const JsonObject& rJsonObject, std::ofstream* pOutFile, bool tabAlreadyInsertFlag)
        {
            // �L�[���擾
            String key = rJsonObject.GetKey();

            // �L�[�ƒ�����( �J )����������
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : \n";
            if (tabAlreadyInsertFlag == false) s_WriteTab(pOutFile);
            *pOutFile << "{\n";

            // �A�z�z����擾
            auto& rObject = *(rJsonObject.ObjectCast());

            // �A�z�z��̃C�e���[�^���擾
            auto iterator = rObject.begin();

            // ���[�v�̏I���𔻒f����t���O
            bool loopFinishFlag = !(iterator != rObject.end());

            // �^�u��1����
            s_WriteTab(nullptr, 1);

            while (loopFinishFlag == false)
            {
                // �^�u��}��
                s_WriteTab(pOutFile);

                // ��ޕʂɏ�������
                s_WriteTypeDistinguish(iterator->second, pOutFile);
                ++iterator;

                // ���[�v�̏I���𔻒f
                if (iterator != rObject.end())
                {
                    *pOutFile << ",\n";
                }
                else
                {
                    loopFinishFlag = true;
                }
            }

            // �^�u��1����
            s_WriteTab(nullptr, -1);

            // ������( �� )����������
            *pOutFile << "\n";
            s_WriteTab(pOutFile);
            *pOutFile << "}";
        }


        /*************************************************************//**
         *
         *  @brief  null�l�̏������݂��s��
         *  @param  JSON�I�u�W�F�N�g
         *  @param  �o�̓X�g���[��
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteNull(const JsonObject& rJsonObject, std::ofstream* pOutFile)
        {
            auto key = rJsonObject.GetKey();
            if (key.empty() == false) *pOutFile << "\"" << key << "\" : ";
            *pOutFile << "null";
        }


        /*************************************************************//**
         *
         *  @brief  �^�u�̏������݂��s��
         *  @param  �o�̓X�g���[��
         *  @param  ������^�u��
         *  @return �Ȃ�
         *
         ****************************************************************/
        static void s_WriteTab(std::ofstream* pOutFile, int32_t addTab = 0)
        {
            // �^�u��
            static int32_t s_tabCount = 0;
            
            // ���v���Ƀ^�u�������Z
            s_tabCount += addTab;
            assert(s_tabCount >= 0);

            if (pOutFile)
            {
                for (int32_t i = 0; i < s_tabCount; ++i)
                {
#ifdef JSON_ENABLE_INSERT_TAB

                    *pOutFile << "\t";

#else

                    *pOutFile << "    ";

#endif
                }
            }
        }

#pragma endregion

    };

    /* �ʖ� */
    using JsonObject = C_JsonObject<>;                                                      // JsonObject�^���ȗ�
    using Character = C_JsonObject<>::Character;                                            // Character�^���ȗ�
    using Integer = C_JsonObject<>::Integer;                                                // Integer�^���ȗ�
    using Real = C_JsonObject<>::Real;                                                      // Real�^���ȗ�
    using Boolean = C_JsonObject<>::Boolean;                                                // Boolean�^���ȗ�
    using String = C_JsonObject<>::String;                                                  // String�^���ȗ�
    using Array = C_JsonObject<>::Array;                                                    // Array�^���ȗ�
    using Object = C_JsonObject<>::Object;                                                  // Object�^���ȗ�
}
