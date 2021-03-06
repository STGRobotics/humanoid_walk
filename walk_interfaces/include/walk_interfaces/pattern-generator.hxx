#ifndef WALK_INTERFACE_PATTERN_GENERATOR_HXX
# define WALK_INTERFACE_PATTERN_GENERATOR_HXX
# include <iostream>

namespace walk
{
  template <typename T>
  PatternGenerator<T>::PatternGenerator()
    : footprints_ (),
      startWithLeftFoot_ (true),
      leftFootTrajectory_(),
      rightFootTrajectory_(),
      centerOfMassTrajectory_(),
      zmpTrajectory_(),
      postureTrajectory_(),
      leftHandTrajectory_(),
      rightHandTrajectory_(),

      initialLeftFootPosition_(),
      initialRightFootPosition_(),
      initialCenterOfMassPosition_(),
      initialPosture_(),

      finalLeftFootPosition_(),
      finalRightFootPosition_(),
      finalCenterOfMassPosition_(),
      finalPosture_()
  {
    initialLeftFootPosition_.setIdentity();
    initialRightFootPosition_.setIdentity();
    initialCenterOfMassPosition_.setZero();
    initialPosture_.setZero();
    initialLeftHandPosition_.setIdentity();
    initialRightHandPosition_.setIdentity();

    finalLeftFootPosition_.setIdentity();
    finalRightFootPosition_.setIdentity();
    finalCenterOfMassPosition_.setZero();
    finalPosture_.setZero();
    finalLeftHandPosition_.setIdentity();
    finalRightHandPosition_.setIdentity();
  }

  template <typename T>
  PatternGenerator<T>::PatternGenerator
  (const PatternGenerator<T>& pg)
    : footprints_ (pg.footprints_),
      startWithLeftFoot_ (pg.startWithLeftFoot_),
      leftFootTrajectory_(pg.leftFootTrajectory_),
      rightFootTrajectory_(pg.rightFootTrajectory_),
      centerOfMassTrajectory_(pg.centerOfMassTrajectory_),
      zmpTrajectory_(pg.zmpTrajectory_),
      postureTrajectory_(pg.postureTrajectory_),
      leftHandTrajectory_(pg.leftHandTrajectory_),
      rightHandTrajectory_(pg.rightHandTrajectory_)
  {}

  template <typename T>
  PatternGenerator<T>&
  PatternGenerator<T>::operator=
  (const PatternGenerator<T>& pg)
  {
    if (&pg == this)
      return *this;
    this->footprints_ = pg.footprints_;
    this->startWithLeftFoot_ = pg.startWithLeftFoot_;
    this->leftFootTrajectory_ = pg.leftFootTrajectory_;
    this->rightFootTrajectory_ = pg.rightFootTrajectory_;
    this->centerOfMassTrajectory_ = pg.centerOfMassTrajectory_;
    this->zmpTrajectory_ = pg.zmpTrajectory_;
    this->postureTrajectory_ = pg.postureTrajectory_;
    this->leftHandTrajectory_ = pg.leftHandTrajectory_;
    this->rightHandTrajectory_ = pg.rightHandTrajectory_;
    return *this;
  }

  template <typename T>
  void
  PatternGenerator<T>::setInitialRobotPosition
  (const HomogeneousMatrix3d& leftFoot,
   const HomogeneousMatrix3d& rightFoot,
   const Vector3d& centerOfMass,
   const Posture& posture)
  {
    initialLeftFootPosition_ = leftFoot;
    initialRightFootPosition_ = rightFoot;
    initialCenterOfMassPosition_ = centerOfMass;
    initialPosture_ = posture;
  }

  template <typename T>
  void
  PatternGenerator<T>::setInitialRobotPosition
  (const HomogeneousMatrix3d& leftFoot,
   const HomogeneousMatrix3d& rightFoot,
   const Vector3d& centerOfMass,
   const Posture& posture,
   const HomogeneousMatrix3d& leftHand,
   const HomogeneousMatrix3d& rightHand)
  {
    initialLeftFootPosition_ = leftFoot;
    initialRightFootPosition_ = rightFoot;
    initialCenterOfMassPosition_ = centerOfMass;
    initialPosture_ = posture;
    initialLeftHandPosition_ = leftHand;
    initialRightHandPosition_ = rightHand;
  }


  template <typename T>
  void
  PatternGenerator<T>::setFinalRobotPosition
  (const HomogeneousMatrix3d& leftFoot,
   const HomogeneousMatrix3d& rightFoot,
   const Vector3d& centerOfMass,
   const Posture& posture)
  {
    finalLeftFootPosition_ = leftFoot;
    finalRightFootPosition_ = rightFoot;
    finalCenterOfMassPosition_ = centerOfMass;
    finalPosture_ = posture;
  }

  template <typename T>
  void
  PatternGenerator<T>::setFinalRobotPosition
  (const HomogeneousMatrix3d& leftFoot,
   const HomogeneousMatrix3d& rightFoot,
   const Vector3d& centerOfMass,
   const Posture& posture,
   const HomogeneousMatrix3d& leftHand,
   const HomogeneousMatrix3d& rightHand)
  {
    finalLeftFootPosition_ = leftFoot;
    finalRightFootPosition_ = rightFoot;
    finalCenterOfMassPosition_ = centerOfMass;
    finalPosture_ = posture;
    finalLeftHandPosition_ = leftHand;
    finalRightHandPosition_ = rightHand;
  }



  template <typename T>
  const typename PatternGenerator<T>::footprints_t&
  PatternGenerator<T>::footprints() const
  {
    return footprints_;
  }

  template <typename T>
  void
  PatternGenerator<T>::setFootprints
  (const footprints_t& footprints, bool startWithLeftFoot)
  {
    footprints_ = footprints;
    startWithLeftFoot_ = startWithLeftFoot;
    this->computeTrajectories();
  }

  template <typename T>
  bool
  PatternGenerator<T>::startWithLeftFoot() const
  {
    return startWithLeftFoot_;
  }

  template <typename T>
  PatternGenerator<T>::~PatternGenerator()
  {}

  template <typename T>
  const typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::leftFootTrajectory() const
  {
    return leftFootTrajectory_;
  }

  template <typename T>
  const typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::rightFootTrajectory() const
  {
    return rightFootTrajectory_;
  }

  template <typename T>
  const typename PatternGenerator<T>::TrajectoryV2d&
  PatternGenerator<T>::zmpTrajectory() const
  {
    return zmpTrajectory_;
  }

  template <typename T>
  const typename PatternGenerator<T>::TrajectoryV3d&
  PatternGenerator<T>::centerOfMassTrajectory() const
  {
    return centerOfMassTrajectory_;
  }

  template <typename T>
  const typename PatternGenerator<T>::TrajectoryNd&
  PatternGenerator<T>::postureTrajectory() const
  {
    return postureTrajectory_;
  }

  template <typename T>
  const typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::leftHandTrajectory() const
  {
    return leftHandTrajectory_;
  }

  template <typename T>
  const typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::rightHandTrajectory() const
  {
    return rightHandTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::getLeftFootTrajectory()
  {
    return leftFootTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::getRightFootTrajectory()
  {
    return rightFootTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::TrajectoryV2d&
  PatternGenerator<T>::getZmpTrajectory()
  {
    return zmpTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::TrajectoryV3d&
  PatternGenerator<T>::getCenterOfMassTrajectory()
  {
    return centerOfMassTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::TrajectoryNd&
  PatternGenerator<T>::getPostureTrajectory()
  {
    return postureTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::getLeftHandTrajectory()
  {
    return leftHandTrajectory_;
  }

  template <typename T>
  typename PatternGenerator<T>::Trajectory3d&
  PatternGenerator<T>::getRightHandTrajectory()
  {
    return rightHandTrajectory_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getInitialLeftFootPosition()
  {
    return initialLeftFootPosition_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getInitialRightFootPosition()
  {
    return initialRightFootPosition_;
  }

  template <typename T>
  Vector3d&
  PatternGenerator<T>::getInitialCenterOfMassPosition()
  {
    return initialCenterOfMassPosition_;
  }

  template <typename T>
  Posture&
  PatternGenerator<T>::getInitialPosture()
  {
    return initialPosture_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getInitialLeftHandPosition()
  {
    return initialLeftHandPosition_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getInitialRightHandPosition()
  {
    return initialRightHandPosition_;
  }


  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getFinalLeftFootPosition()
  {
    return finalLeftFootPosition_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getFinalRightFootPosition()
  {
    return finalRightFootPosition_;
  }

  template <typename T>
  Vector3d&
  PatternGenerator<T>::getFinalCenterOfMassPosition()
  {
    return finalCenterOfMassPosition_;
  }

  template <typename T>
  Posture&
  PatternGenerator<T>::getFinalPosture()
  {
    return finalPosture_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getFinalLeftHandPosition()
  {
    return finalLeftHandPosition_;
  }

  template <typename T>
  HomogeneousMatrix3d&
  PatternGenerator<T>::getFinalRightHandPosition()
  {
    return finalRightHandPosition_;
  }




  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::initialLeftFootPosition() const
  {
    return initialLeftFootPosition_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::initialRightFootPosition() const
  {
    return initialRightFootPosition_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::initialLeftHandPosition() const
  {
    return initialLeftHandPosition_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::initialRightHandPosition() const
  {
    return initialRightHandPosition_;
  }


  template <typename T>
  const Vector3d&
  PatternGenerator<T>::initialCenterOfMassPosition() const
  {
    return initialCenterOfMassPosition_;
  }

  template <typename T>
  const Posture&
  PatternGenerator<T>::initialPosture() const
  {
    return initialPosture_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::finalLeftFootPosition() const
  {
    return finalLeftFootPosition_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::finalRightFootPosition() const
  {
    return finalRightFootPosition_;
  }

  template <typename T>
  const Vector3d&
  PatternGenerator<T>::finalCenterOfMassPosition() const
  {
    return finalCenterOfMassPosition_;
  }

  template <typename T>
  const Posture&
  PatternGenerator<T>::finalPosture() const
  {
    return finalPosture_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::finalLeftHandPosition() const
  {
    return finalLeftHandPosition_;
  }

  template <typename T>
  const HomogeneousMatrix3d&
  PatternGenerator<T>::finalRightHandPosition() const
  {
    return finalRightHandPosition_;
  }


  template <typename T>
  std::ostream&
  operator<<(std::ostream& os, const PatternGenerator<T>& pg)
  {
    os
      << "initial left foot position:\n"
      << pg.initialLeftFootPosition()
      << "initial right foot position:\n"
      << pg.initialRightFootPosition()
      << "initial center of mass position:\n"
      << pg.initialCenterOfMassPosition()
      << "initial posture:\n"
      << pg.initialPosture()

      << "final left foot position:\n"
      << pg.finalLeftFootPosition()
      << "final right foot position:\n"
      << pg.finalRightFootPosition()
      << "final center of mass position:\n"
      << pg.finalCenterOfMassPosition()
      << "final posture:\n"
      << pg.finalPosture()

      << "left foot trajectory:\n"
      << pg.leftFootTrajectory()
      << "right foot trajectory:\n"
      << pg.rightFootTrajectory()
      << "zmp trajectory:\n"
      << pg.zmpTrajectory()
      << "center of mass trajectory:\n"
      << pg.centerOfMassTrajectory()
      << "left hand trajectory:\n"
      << pg.leftHandTrajectory()
      << "right hand trajectory:\n"
      << pg.rightHandTrajectory();
    return os;
  }
} // end of namespace walk.

#endif //! WALK_INTERFACE_PATTERN_GENERATOR_HXX
