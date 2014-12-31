/* ��d�C���N���[�h�h�~ */
#pragma once


/* �O���錾 */
namespace Math
{
    template<typename T>
    struct S_Vector2;
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
    using Point2 = Math::S_Vector2<T>;          // Point2�^


    //-------------------------------------------------------------
    //!
    //! @brief �f�B�e�N�V����2D
    //! @brief 2D�̏Փ˔���̊֐����܂Ƃ߂����[�e�B���e�B�N���X
    //!
    //-------------------------------------------------------------
    template<typename T = float>
    class C_Detection2D
    {
    public:
        /* �ʖ� */
        using Point2 = Point2<T>;               // Point2�^���ȗ�


        /* ��`���m�̏Փ˔��� */
        static bool s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                 T halfWidth,
                                                 T halfHeight,
                                                 const Point2& rAnotherCenterPosition,
                                                 T anotherHalfWidth,
                                                 T anotherHalfHeihgt);

        static bool s_CheckRectangleAndRectangle(const Point2& rCenterPosition,
                                                 T halfWidth,
                                                 T halfHeight,
                                                 T angle,
                                                 const Point2& rAnotherCenterPosition,
                                                 T anotherHalfWidth,
                                                 T anotherHalfHeight,
                                                 T anotherAngle);

        /* �~���m�̏Փ˔��� */
        static bool s_CheckCircleAndCircle(const Point2& rCenterPosition,
                                           T radius,
                                           const Point2& rAnotherCenterPosition,
                                           T anotherRadius);

        /* ��`�Ɖ~�̏Փ˔��� */
        static bool s_CheckRectangleAndCircle(const Point2& rRectangleCenterPosition,
                                              T rectangleHalfWidth,
                                              T rectangleHalfHeight,
                                              T rectangleAngle,
                                              const Point2& rCircleCenterPosition,
                                              T circleRadius);

        /* �~�Ɠ_�̏Փ˔��� */
        static bool s_CheckCircleAndPoint(const Point2& rCircleCenterPosition,
                                          T circleRadius,
                                          const Point2& rPoint);

        /* �~�Ɛ����̏Փ˔��� */
        static bool s_CheckCircleAndSegment(const Point2& rCircleCenterPosition,
                                            T circleRadius,
                                            const Point2& rSegmentBeginPoint,
                                            const Point2& rSegmentEndPoint);

        /* �_�Ɠ_�̏Փ˔��� */
        static bool s_CheckPointAndPoint(const Point2& rPoint,
                                         const Point2& rAnotherPoint);

        /* �_�Ɛ����̏Փ˔��� */
        static bool s_CheckPointAndSegment(const Point2& rPoint,
                                           const Point2& rSegmentBeginPoint,
                                           const Point2& rSegmentEndPoint);

        /* �_�Ƒȉ~�̏Փ˔��� */
        static bool s_CheckPointAndEllipse(const Point2& rPoint,
                                           const Point2& rEllipseCenterPosition,
                                           const Point2& rEllipseSemidiameter,
                                           T ellipseAngle);

        /* �����Ɛ����̏Փ˔��� */
        static bool s_CheckSegmentAndSegment(const Point2& rBeginPoint,
                                             const Point2& rEndPoint,
                                             const Point2& rAnotherBeginPoint,
                                             const Point2& rAnotherEndPoint,
                                             Point2* pIntersectionPoint);
    };
}
