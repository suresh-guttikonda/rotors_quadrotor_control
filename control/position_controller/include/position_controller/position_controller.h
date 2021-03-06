/**
 *  @file   position_controller.h
 *  @brief  quadrotor's position control related functionality declaration & definition
 *  @author neo
 *  @data   03.10.2021
 */
#ifndef POSITION_CONTROLLER_POSITION_CONTROLLER_H
#define POSITION_CONTROLLER_POSITION_CONTROLLER_H

// 3rd party dependencies
#include <Eigen/Dense>

// quadrotor_common dependencies
#include "quadrotor_common/quadrotor_control_command.h"
#include "quadrotor_common/quadrotor_state_estimate.h"
#include "quadrotor_common/quadrotor_trajectory_point.h"

namespace position_controller {

/**
 *  @brief  PositionController class implementation.
 *  @detail The high-level position control outputs the desired orientation, the desired collective thrust command,
 *          the desired body rates, and the desired angular acceleration.
 *          Let {x_W, y_W, z_W} represents world frame W,
 *              {x_B, y_B, z_B} represents body frame B expressed in world coordinate frame and
 *              {x_C, y_C, z_C} represents intermediate frame C obtained by rotation W by angle = quadrotor orientation.
 *          for further information:
 *            + Theory behind algorithms
 *              https://github.com/uzh-rpg/rpg_quadrotor_control/blob/master/documents/theory_and_math/theory_and_math.pdf
 *            + Differential Flatness of Quadrotor Dynamics Subject to Rotor Drag for Accurate Tracking of
 *              High-Speed Trajectories https://arxiv.org/pdf/1712.02402.pdf
 *            + Thrust Mixing, Saturation, and Body-Rate Control for Accurate Aggressive Quadrotor Flight
 *              https://www.ifi.uzh.ch/dam/jcr:5f3668fe-1d4e-4c2b-a190-8f5608f40cf3/RAL16_Faessler.pdf
 */
class PositionController {
 public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW

        ///////////////////////////////////////////////////
        //////////// Constructors & Destructors ///////////
        ///////////////////////////////////////////////////

    /**
     *  @brief  PositionController's default constructor, called when an instance is created.
     */
    PositionController();

    /**
     *  @brief  PositionController's default destructor, called when an instance is destroyed.
     */
    ~PositionController();

        //////////////////////////////////////
        //////////// Class Methods ///////////
        //////////////////////////////////////

    /**
     *  @brief  Compute the high level position control outputs to track input trajectory point.
     *  @detail To achieve accurate tracking of a reference trajectory point, the position controller takes the reference
     *          inputs as feed-forward terms. Using the differential flatness property of quadrotor dynamics
     *          subject to rotor drag we can compute required reference (desired) quantities:
     *            orientation, thrust, bodyrates and angular acceleration.
     *  @param  state_estimate    -
     *  @param  reference_state   -
     *  @return control_command   -
     */
    quadrotor_common::QuadrotorControlCommand run(
        const quadrotor_common::QuadrotorStateEstimate& state_estimate,
        const quadrotor_common::QuadrotorTrajectoryPoint& reference_state);

 private:

        //////////////////////////////////
        //////////// Constants ///////////
        //////////////////////////////////

        //////////////////////////////////////
        //////////// Class Methods ///////////
        //////////////////////////////////////

    /**
     *  @brief
     *  @detail
     *  @param  reference_state   -
     *  @param  attitude_estimate -
     *  @return  control_command  -
     */
    quadrotor_common::QuadrotorControlCommand computeReferenceInputs(
        const quadrotor_common::QuadrotorStateEstimate& state_estimate,
        const quadrotor_common::QuadrotorTrajectoryPoint& reference_state) const;

};  /* class PositionController */

} /* namespace position_controller */

#endif  /* POSITION_CONTROLLER_POSITION_CONTROLLER_H */
