
/*
 * Copyright (C) 2000-2001 QuantLib Group
 *
 * This file is part of QuantLib.
 * QuantLib is a C++ open source library for financial quantitative
 * analysts and developers --- http://quantlib.sourceforge.net/
 *
 * QuantLib is free software and you are allowed to use, copy, modify, merge,
 * publish, distribute, and/or sell copies of it under the conditions stated
 * in the QuantLib License.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the license for more details.
 *
 * You should have received a copy of the license along with this file;
 * if not, contact ferdinando@ametrano.net
 * The license is also available at http://quantlib.sourceforge.net/LICENSE.TXT
 *
 * The members of the QuantLib Group are listed in the Authors.txt file, also
 * available at http://quantlib.sourceforge.net/Authors.txt
*/

/*! \file multifactorpricer.hpp

    $Id$
*/

// $Source$
// $Log$
// Revision 1.5  2001/05/24 15:38:08  nando
// smoothing #include xx.hpp and cutting old Log messages
//

#ifndef quantlib_montecarlo_multi_factor_pricer_h
#define quantlib_montecarlo_multi_factor_pricer_h

#include "ql/MonteCarlo/multifactormontecarlooption.hpp"

namespace QuantLib {

    namespace Pricers {
        //! Base class for multi-factor Monte Carlo pricers
        /*! MultiFactorPricer is the base class for the Monte Carlo pricers
            depending from more than one factor. Eventually it might be linked
            to the general tree of pricers, in order to have available tools
            like impliedVolaitlity. Also, it will, eventually, implement the
            calculation of greeks in montecarlo methods.
            Deriving a class from MultiFactorPricer gives an easy way to write
            a multi-factor Monte Carlo Pricer.
            See PlainBasketOption for an example
        */

        class MultiFactorPricer {
        public:
            MultiFactorPricer() : isInitialized_(false){}
            MultiFactorPricer(long samples, long seed=0);
            ~MultiFactorPricer(){}
            virtual double value() const;
            virtual double errorEstimate() const;
        protected:
            bool isInitialized_;
            long seed_;
            mutable long samples_;
            mutable MonteCarlo::MultiFactorMonteCarloOption montecarloPricer_;
        };

        inline MultiFactorPricer::MultiFactorPricer(long samples, long seed):
                    samples_(samples), seed_(seed), isInitialized_(true){}

        inline double MultiFactorPricer::value() const{
            QL_REQUIRE(isInitialized_,
                "MultiFactorPricer::value has not been initialized");
            return montecarloPricer_.sampleAccumulator(samples_).mean();
        }

        inline double MultiFactorPricer::errorEstimate() const {
            QL_REQUIRE(isInitialized_,
                "MultiFactorPricer::errorEstimate has not been initialized");
            return montecarloPricer_.sampleAccumulator().errorEstimate();
        }

    }

}

#endif
