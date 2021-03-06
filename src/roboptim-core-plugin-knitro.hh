// Copyright (C) 2014 by Thomas Moulard, AIST, CNRS.
//
// This file is part of the roboptim.
//
// roboptim is free software: you can redistribute it and/or modify
// it under the terms of the GNU Lesser General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// roboptim is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Lesser General Public License for more details.
//
// You should have received a copy of the GNU Lesser General Public License
// along with roboptim.  If not, see <http://www.gnu.org/licenses/>.

#ifndef ROBOPTIM_CORE_PLUGIN_KNITRO_HH
# define ROBOPTIM_CORE_PLUGIN_KNITRO_HH
# include <roboptim/core/portability.hh>
# include <iostream>
# include <string>
# include <utility>
# include <vector>

# include <boost/mpl/vector.hpp>

# include <boost/variant.hpp>
# include <roboptim/core/derivable-function.hh>
# include <roboptim/core/linear-function.hh>
# include <roboptim/core/solver.hh>
# include <roboptim/core/util.hh>

/// \brief KNITRO Context pre-declaration.
class KTR_context;

namespace roboptim
{
  /// \addtogroup roboptim_solver
  /// @{

  /// \brief KNITRO based solver.
  class ROBOPTIM_DLLEXPORT KNITROSolver
    : public Solver<GenericDifferentiableFunction<EigenMatrixDense>,
		    boost::mpl::vector<
		      GenericLinearFunction<EigenMatrixDense>,
		      GenericDifferentiableFunction<EigenMatrixDense> > >
  {
    /// \brief CLIST parameter passed to parent.
    typedef boost::mpl::vector<
      GenericLinearFunction<EigenMatrixDense>,
      GenericDifferentiableFunction<EigenMatrixDense> >
    clist_t;

public:
    typedef problem_t::function_t::matrix_t matrix_t;
    typedef problem_t::function_t::value_type value_type;
    typedef problem_t::vector_t vector_t;

    /// \brief Parent type.
    typedef Solver<GenericDifferentiableFunction<EigenMatrixDense>, clist_t>
      parent_t;

    /// \brief Instantiate the solver from a problem.
    ///
    /// \param problem problem that will be solved
    explicit KNITROSolver (const problem_t& problem) throw ();

    virtual ~KNITROSolver () throw ();

    /// \brief Solve the problem.
    virtual void solve () throw ();

    /// \brief Display the solver on the specified output stream.
    ///
    /// \param o output stream used for display
    /// \return output stream
    virtual std::ostream& print (std::ostream& o) const throw ();

    void setIterationCallback (callback_t callback) throw (std::runtime_error);

    const callback_t& callback () const throw ()
    {
      return callback_;
    }

    solverState_t& solverState () throw ()
    {
      return solverState_;
    }

  protected:
    int computeConstraintsSize () throw ();

  private:
    /// \brief Per-iteration callback
    callback_t callback_;

    /// \brief Current state of the solver (used by the callback function).
    solverState_t solverState_;

    KTR_context* knitro_;
  };

  /// @}

} // end of namespace roboptim

#endif //! ROBOPTIM_CORE_PLUGIN_KNITRO_HH

//  LocalWords:  KNITRO
