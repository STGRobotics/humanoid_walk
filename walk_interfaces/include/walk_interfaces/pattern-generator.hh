#ifndef WALK_INTERFACE_WALK_HH
# define WALK_INTERFACE_WALK_HH
# include <vector>

# include <boost/static_assert.hpp>

# include <walk_interfaces/types.hh>
# include <walk_interfaces/discretized-trajectory.hh>
# include <walk_interfaces/stamped-footprint.hh>

namespace walk
{
  template <typename T>
  class PatternGenerator;

  template <typename T>
  struct PatternGeneratorTraits
  {
    BOOST_STATIC_ASSERT(sizeof(T) == 0);
  };

  /// \brief A pattern generator computes walking reference
  /// trajectories.
  ///
  ///
  /// This class is the core of walk_interfaces. A pattern generator
  /// computes the reference trajectories of associated with a given
  /// walking movement.
  ///
  ///
  /// The frames follows the ROS conventions (X forward, Y left and Z
  /// up).
  ///
  /// The reference trajectories are:
  ///
  /// - The two feet (left and right) trajectories (\f$SO(3)\f$). The
  ///   (X, Y) plan of the frame is coplanar with the foot contact
  ///   surface. The origin matches the center of this surface.
  ///
  /// - The center of mass trajectory (\f$R^3\f$).
  ///
  /// - The Zero Momentum Point trajectory (\f$R^2\f$).
  ///
  /// - An optional posture trajectory (\f$R^n\f$). This trajectory is
  ///   in the joint space. The order and semantics of the joints are
  ///   algorithm specific. Please see the pattern generator
  ///   documentation for more details.
  ///
  /// \tparam T Pattern generator concrete type.
  template <typename T>
  class PatternGenerator
  {
  public:
    typedef T concreteType_t;

    /// \brief Footprint type.
    typedef typename PatternGeneratorTraits<concreteType_t>::Footprint
    footprint_t;

    /// \brief DiscretizedTrajectory in \f$SO(3)\f$.
    typedef typename PatternGeneratorTraits<concreteType_t>::Trajectory3d
    Trajectory3d;
    /// \brief DiscretizedTrajectory in \f$SO(3)\f$.
    typedef typename PatternGeneratorTraits<concreteType_t>::Trajectory2d
    Trajectory2d;
    /// \brief DiscretizedTrajectory in \f$R^2\f$.
    typedef typename PatternGeneratorTraits<concreteType_t>::TrajectoryV2d
    TrajectoryV2d;
    /// \brief DiscretizedTrajectory in \f$R^3\f$.
    typedef typename PatternGeneratorTraits<concreteType_t>::TrajectoryV3d
    TrajectoryV3d;
    /// \brief DiscretizedTrajectory in \f$R^n\f$.
    typedef typename PatternGeneratorTraits<concreteType_t>::TrajectoryNd
    TrajectoryNd;

    /// \brief Vector of footprints.
    typedef WALK_INTERFACES_EIGEN_STL_VECTOR(footprint_t) footprints_t;

    /// \name Constructor and destructor.
    /// \{

    /// \brief Default constructor.
    explicit PatternGenerator();
    /// \brief Copy constructor.
    explicit PatternGenerator(const PatternGenerator<T>&);
    /// \brief Destructor.
    virtual ~PatternGenerator();

    /// \}

    /// \brief Assignment operator.
    PatternGenerator<T>& operator=(const PatternGenerator<T>&);

    /// \brief Define the initial robot state.
    ///
    /// \param leftFoot left foot initial position.
    /// \param rightFoot right foot initial position.
    /// \param centerOfMass center of mass initial position.
    /// \param posture initial posture.
    void setInitialRobotPosition(const HomogeneousMatrix3d& leftFoot,
				 const HomogeneousMatrix3d& rightFoot,
				 const Vector3d& centerOfMass,
				 const Posture& posture);

    /// \brief Define the initial robot state.
    ///
    /// \param leftFoot left foot initial position.
    /// \param rightFoot right foot initial position.
    /// \param centerOfMass center of mass initial position.
    /// \param posture initial posture.
    /// \param leftHand left hand initial position.
    /// \param rightHand right hand initial position.
    void setInitialRobotPosition(const HomogeneousMatrix3d& leftFoot,
				 const HomogeneousMatrix3d& rightFoot,
				 const Vector3d& centerOfMass,
				 const Posture& posture,
				 const HomogeneousMatrix3d& leftHand,
				 const HomogeneousMatrix3d& rightHand);


    /// \brief Define the final robot state.
    ///
    /// \param leftFoot left foot final position.
    /// \param rightFoot right foot final position.
    /// \param centerOfMass center of mass final position.
    /// \param posture final posture.
    void setFinalRobotPosition(const HomogeneousMatrix3d& leftFoot,
			       const HomogeneousMatrix3d& rightFoot,
			       const Vector3d& centerOfMass,
			       const Posture& posture);

    /// \brief Define the final robot state.
    ///
    /// \param leftFoot left foot final position.
    /// \param rightFoot right foot final position.
    /// \param centerOfMass center of mass final position.
    /// \param posture final posture.
    /// \param leftHand left hand final position.
    /// \param rightHand right hand final position.
    void setFinalRobotPosition(const HomogeneousMatrix3d& leftFoot,
			       const HomogeneousMatrix3d& rightFoot,
			       const Vector3d& centerOfMass,
			       const Posture& posture,
			       const HomogeneousMatrix3d& leftHand,
			       const HomogeneousMatrix3d& rightHand);


    /// \brief Set the footprint sequence for the pattern generator.
    ///
    /// \param startWithLeftFoot True if the movement first flying
    /// foot is the left foot, false otherwise. It is then assumed
    /// that the footprints alternate between left and right.
    void setFootprints(const footprints_t&, bool startWithLeftFoot);

    /// Footprints getter.
    const footprints_t& footprints() const;

    /// Is the first flying foot the left one?
    bool startWithLeftFoot() const;

    /// \name Trajectories.
    /// \{

    /// \brief Left foot trajectory getter.
    const Trajectory3d& leftFootTrajectory() const;
    /// \brief Right foot trajectory getter.
    const Trajectory3d& rightFootTrajectory() const;
    /// \brief ZMP trajectory getter.
    const TrajectoryV2d& zmpTrajectory() const;
    /// \brief Center of mass trajectory getter.
    const TrajectoryV3d& centerOfMassTrajectory() const;
    /// \brief Posture trajectory getter.
    const TrajectoryNd& postureTrajectory() const;

    /// \brief Left hand trajectory getter.
    const Trajectory3d& leftHandTrajectory() const;
    /// \brief Right hand trajectory getter.
    const Trajectory3d& rightHandTrajectory() const;

    /// \}

    /// \name Initial configuration.
    /// \{

    /// \brief Initial left foot position getter.
    const HomogeneousMatrix3d& initialLeftFootPosition() const;
    /// \brief Initial right foot position getter.
    const HomogeneousMatrix3d& initialRightFootPosition() const;
    /// \brief Initial center of  mass getter.
    const Vector3d& initialCenterOfMassPosition() const;
    /// \brief Initial posture getter.
    const Posture& initialPosture() const;
    /// \brief Initial left hand position getter.
    const HomogeneousMatrix3d& initialLeftHandPosition() const;
    /// \brief Initial right hand position getter.
    const HomogeneousMatrix3d& initialRightHandPosition() const;

    /// \}


    /// \name Final configuration
    /// \{

    /// \brief Final left foot position getter.
    const HomogeneousMatrix3d& finalLeftFootPosition() const;
    /// \brief Final right foot position getter.
    const HomogeneousMatrix3d& finalRightFootPosition() const;
    /// \brief Final center of mass position getter.
    const Vector3d& finalCenterOfMassPosition() const;
    /// \brief Final posture getter.
    const Posture& finalPosture() const;
    /// \brief Final left hand position getter.
    const HomogeneousMatrix3d& finalLeftHandPosition() const;
    /// \brief Final right hand position getter.
    const HomogeneousMatrix3d& finalRightHandPosition() const;

    /// \}

  protected:
    /// \brief Left foot trajectory setter.
    Trajectory3d& getLeftFootTrajectory();
    /// \brief Right foot trajectory setter.
    Trajectory3d& getRightFootTrajectory();
    /// \brief ZMP trajectory setter.
    TrajectoryV2d& getZmpTrajectory();
    /// \brief Center of mass trajectory setter.
    TrajectoryV3d& getCenterOfMassTrajectory();
    /// \brief Posture trajectory setter.
    TrajectoryNd& getPostureTrajectory();
    /// \brief Left hand trajectory setter.
    Trajectory3d& getLeftHandTrajectory();
    /// \brief Right hand trajectory setter.
    Trajectory3d& getRightHandTrajectory();

    /// \brief Initial left foot position setter.
    HomogeneousMatrix3d& getInitialLeftFootPosition();
    /// \brief Initial right foot position setter.
    HomogeneousMatrix3d& getInitialRightFootPosition();
    /// \brief Initial center of mass position setter.
    Vector3d& getInitialCenterOfMassPosition();
    /// \brief Initial posture setter.
    Posture& getInitialPosture();
    /// \brief Initial left hand position setter.
    HomogeneousMatrix3d& getInitialLeftHandPosition();
    /// \brief Initial right hand position setter.
    HomogeneousMatrix3d& getInitialRightHandPosition();

    /// \brief Final left foot position setter.
    HomogeneousMatrix3d& getFinalLeftFootPosition();
    /// \brief Final right foot position setter.
    HomogeneousMatrix3d& getFinalRightFootPosition();
    /// \brief Final center of mass position setter.
    Vector3d& getFinalCenterOfMassPosition();
    /// \brief Final posture setter.
    Posture& getFinalPosture();
    /// \brief Final left hand position setter.
    HomogeneousMatrix3d& getFinalLeftHandPosition();
    /// \brief Final right hand position setter.
    HomogeneousMatrix3d& getFinalRightHandPosition();


    /// \brief Compute the reference trajectories.
    ///
    /// This abstract virtual method must be defined in the child
    /// classes. It must compute the reference trajectories and fill
    /// the different attributes of this class using the protected
    /// setters.
    virtual void computeTrajectories() = 0;

  private:
    /// \brief Footprint sequence.
    footprints_t footprints_;
    /// \brief Is the left foot the first flying foot?
    bool startWithLeftFoot_;
    /// \brief Left foot trajectory.
    Trajectory3d leftFootTrajectory_;
    /// \brief Right foot trajectory.
    Trajectory3d rightFootTrajectory_;
    /// \brief Center of mass trajectory.
    TrajectoryV3d centerOfMassTrajectory_;
    /// \brief ZMP trajectory.
    TrajectoryV2d zmpTrajectory_;
    /// \brief Posture trajectory.
    TrajectoryNd postureTrajectory_;
    /// \brief Left hand trajectory.
    Trajectory3d leftHandTrajectory_;
    /// \brief Right hand trajectory.
    Trajectory3d rightHandTrajectory_;


    /// \brief Initial left foot position.
    HomogeneousMatrix3d initialLeftFootPosition_;
    /// \brief Initial right foot position.
    HomogeneousMatrix3d initialRightFootPosition_;
    /// \brief Initial center of mass position.
    Vector3d initialCenterOfMassPosition_;
    /// \brief Initial posture.
    Posture initialPosture_;
    /// \brief Initial left hand position.
    HomogeneousMatrix3d initialLeftHandPosition_;
    /// \brief Initial right hand position.
    HomogeneousMatrix3d initialRightHandPosition_;

    /// \brief Final left foot position.
    HomogeneousMatrix3d finalLeftFootPosition_;
    /// \brief Final right foot position.
    HomogeneousMatrix3d finalRightFootPosition_;
    /// \brief Final center of mass position.
    Vector3d finalCenterOfMassPosition_;
    /// \brief Final posture.
    Posture finalPosture_;
    /// \brief Final left hand position.
    HomogeneousMatrix3d finalLeftHandPosition_;
    /// \brief Final right hand position.
    HomogeneousMatrix3d finalRightHandPosition_;
  public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
  };

  /// \brief Display a pattern generator.
  ///
  /// \param stream Output stream.
  /// \param pg Pattern generator.
  template <typename T>
  std::ostream& operator<<(std::ostream& stream,
			   const PatternGenerator<T>& pg);


  class DiscretizedPatternGenerator2d;
  template <>
  struct PatternGeneratorTraits<DiscretizedPatternGenerator2d>
  {
    /// \brief Footprint definition.
    typedef StampedFootprint2d Footprint;

    /// \brief Trajectory in \f$SO(3)\f$.
    typedef DiscretizedTrajectory<StampedPosition3d> Trajectory3d;
    /// \brief Trajectory in \f$SO(2)\f$.
    typedef DiscretizedTrajectory<StampedPosition2d> Trajectory2d;
    /// \brief Trajectory in \f$R^2\f$.
    typedef DiscretizedTrajectory<StampedVector2d> TrajectoryV2d;
    /// \brief Trajectory in \f$R^3\f$.
    typedef DiscretizedTrajectory<StampedVector3d> TrajectoryV3d;
    /// \brief Trajectory in \f$R^n\f$.
    typedef DiscretizedTrajectory<StampedVectorNd> TrajectoryNd;
  };


  class DiscretizedPatternGenerator2d
    : public PatternGenerator<DiscretizedPatternGenerator2d>
  {};

} // end of namespace walk.

# include <walk_interfaces/pattern-generator.hxx>
#endif //! WALK_INTERFACE_WALK_HH
