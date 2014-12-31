/* ��d�C���N���[�h�h�~ */
#pragma once


/* �O���錾 */
namespace Math
{
    template<typename T>
    struct S_Vector3;
};


//-------------------------------------------------------------
//!
//! @brief �R���W����
//! @brief �Փˊ֘A�̖��O���
//!
//-------------------------------------------------------------
namespace Collision
{
    /* �ʖ� */
    template<typename T>
    using Point3 = Math::S_Vector3<T>;           // Point3�^


    //-------------------------------------------------------------
    //!
    //! @brief �f�B�e�N�V����2D
    //! @brief 3D�̏Փ˔���̊֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    template<typename T>
    class C_Detection3D
    {
    public:
        /* �ʖ� */
        using Point3 = Point3<T>;               // Point3�^���ȗ�


        /* �_�Ɛ����̏Փ˔��� */
        static bool s_CheckPointAndSegment(const Point3& rPoint,
                                           const Point3& rSegmentBeginPoint,
                                           const Point3& rSegmentEndPoint);

        /* �����ƕ��ʂ̏Փ˔��� */
        static bool s_CheckSegmentAndPlane(const Point3& rSegmentBeginPoint,
                                           const Point3& rSegmentEndPoint,
                                           const Point3& rPlanePoint,
                                           const Point3& rPlaneNomal);

        /* ���Ƌ��̏Փ˔��� */
        static bool s_CheckSphereAndSphere(const Point3& rCenterPosition,
                                           T radius,
                                           const Point3& rAnotherCenterPosition,
                                           T anotherRadius);

        /* �_���畽�ʂ܂ł̋������擾 */
        static T s_GetLengthFromPointToPlane(const Point3& rPoint,
                                             const Point3& rPlanePoint,
                                             const Point3& rPlaneNormal);
    };
}
