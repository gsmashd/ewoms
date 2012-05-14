// -*- mode: C++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*-
// vi: set et ts=4 sw=4 sts=4:
/*****************************************************************************
 *   Copyright (C) 2011 by Klaus Mosthaf                                     *
 *   Copyright (C) 2008-2009 by Bernd Flemisch                               *
 *   Copyright (C) 2008-2012 by Andreas Lauser                               *
 *   Institute for Modelling Hydraulic and Environmental Systems             *
 *   University of Stuttgart, Germany                                        *
 *   email: <givenname>.<name>@iws.uni-stuttgart.de                          *
 *                                                                           *
 *   This program is free software: you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation, either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program.  If not, see <http://www.gnu.org/licenses/>.   *
 *****************************************************************************/

/*!
 * \file
 *
 * \brief Defines the indices required for the non-isothermal
 *        compositional Stokes box model.
 */
#ifndef DUMUX_STOKES_NI_INDICES_HH
#define DUMUX_STOKES_NI_INDICES_HH

#include <dumux/freeflow/stokes/stokesindices.hh>

namespace Dumux
{
/*!
 * \ingroup BoxStokesNIModel
 * \ingroup BoxIndices
 * \brief Enumerations for the non-isothermal compositional Stokes model
 */
template <class TypeTag, int PVOffset=0>
struct StokesNIIndices : public StokesIndices<TypeTag, PVOffset>
{
    typedef typename GET_PROP_TYPE(TypeTag, GridView) GridView;
    typedef typename GET_PROP_TYPE(TypeTag, FluidSystem) FluidSystem;

    static const int dimWorld = GridView::dimensionworld;
    static const int numComponents = FluidSystem::numComponents;

public:
    //! The index for the energy balance equation.
    static const int energyEqIdx = PVOffset + dimWorld + numComponents;
    //! The index for temperature in primary variable vectors.
    static const int temperatureIdx = PVOffset + dimWorld + numComponents;
};
} // end namespace

#endif