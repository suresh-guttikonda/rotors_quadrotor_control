/**
 *  @file   reference_inputs.h
 *  @brief  quadrotor position control's reference inputs related functionality declaration & definition
 *  @author thor
 *  @date   17.11.2021
 */
#ifndef POSITION_CONTROLLER_REFERENCE_INPUTS_H
#define POSITION_CONTROLLER_REFERENCE_INPUTS_H

//  3rd party dependencies
#include <Eigen/Dense>

//  quadrotor_common dependencies
#include "quadrotor_common/math.h"
#include "quadrotor_common/quadrotor_state_estimate.h"
#include "quadrotor_common/quadrotor_trajectory_point.h"

namespace position_controller {

/**
 *  @brief  ReferenceInputs class implementation
 *  @detail Compute the desirted orientation, the desired collective thrust command,
 *          the desired body rates (angular velocity) and the desires angular acceleration;
 *          required for high-level position control.
 */
class ReferenceInputs {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        /////////////////////////////////////////////////////
        ////////////  Constructors & Destructors  ///////////
        /////////////////////////////////////////////////////

    /**
     *  @brief  ReferenceInputs' default constructor, called when an instance is created
     */
    ReferenceInputs(
        const quadrotor_common::QuadrotorStateEstimate& state_est,
        const quadrotor_common::QuadrotorTrajectoryPoint& state_ref);

    /**
     *  @brief  ReferenceInputs' default destructor, called when an instance is destroyed
     */
    ~ReferenceInputs();

        ////////////////////////////////////////
        ////////////  Class Methods  ///////////
        ////////////////////////////////////////

    /**
     *  @brief  Compute the robust reference orientation R = [x_B, y_B, z_B]
     *  @detail for x_B refer computeRobustBodyXAxis()
     *          for y_B refer computeRobustBodyYAxis()
     */
    void computeReferenceOrientation();

private:

        ////////////////////////////////////
        ////////////  Constants  ///////////
        ////////////////////////////////////

    //  @brief  The gravity acting in -ve z_W direction i.e kGravity_ = -g.z_W
    const Eigen::Vector3d kGravity_ = Eigen::Vector3d(0.0, 0.0, -9.81);

    //  @brief  The almost zero value threshold
    static constexpr double kAlmostZeroValueThreshold_ = 0.001;

        ////////////////////////////////////////
        ////////////  Class Methods  ///////////
        ////////////////////////////////////////

    /**
     *  @brief  Compute robust x_B from the input constraints, where x_B = (y_C x alpha)
     *  @detail Handle singularities when y_C is aligned with alpha or alpha = 0.
     *          For an extreme case solution we set x_B = x_C.
     */
    Eigen::Vector3d computeRobustBodyXAxis() const;

    /**
     *  @brief  Compute robust y_B from the input constraints, where y_B = (beta x x_B)
     *  @detail Handle singularities when x_B is aligned with beta or beta = 0.
     *          For an extreme case solution we set y_B = y_C.
     */
    Eigen::Vector3d computeRobustBodyYAxis() const;

        ////////////////////////////////////////
        ////////////  Class Members  ///////////
        ////////////////////////////////////////

    //  @brief  Input quadrotor's current state estimate
    quadrotor_common::QuadrotorStateEstimate state_estimate;

    //  @brief  Input quadrotor's reference state to track
    quadrotor_common::QuadrotorTrajectoryPoint reference_state;

    //  @brief  quadrotor's reference orientation input
    Eigen::Vector3d x_B, y_B, z_B;
    Eigen::Quaterniond orientation;

    //  @brief  Constraints to enfore reference heading phi
    Eigen::Vector3d x_C, y_C;

    // TODO: get the values from config
    //  @brief  Rotor drag constants
    double dx = 0, dy = 0, dz = 0;

};  /*  class ReferenceInputs  */

} /*  namespace position_controller  */

#endif  /*  POSITION_CONTROLLER_REFERENCE_INPUTS_H  */
