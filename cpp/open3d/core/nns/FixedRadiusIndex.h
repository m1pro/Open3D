// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

#include <vector>

#include "open3d/core/Tensor.h"

namespace open3d {
namespace core {
namespace nns {

/// \class FixedRadiusIndex
///
/// \brief FixedRadiusIndex for nearest neighbor range search.
class FixedRadiusIndex {
public:
    /// \brief Default Constructor.
    FixedRadiusIndex();

    /// \brief Parameterized Constructor.
    ///
    /// \param tensor Provides a set of data points as Tensor for KDTree
    /// construction.
    FixedRadiusIndex(const Tensor &dataset_points);
    ~FixedRadiusIndex();
    FixedRadiusIndex(const FixedRadiusIndex &) = delete;
    FixedRadiusIndex &operator=(const FixedRadiusIndex &) = delete;

public:
    /// Set the data for the spatial hash map from a Tensor.
    ///
    /// \param dataset_points Dataset points for spatial hash map construction.
    /// Must be 2D, with shape {n, d}.
    /// \return Returns true if the construction success, otherwise false.
    bool SetTensorData(const Tensor &dataset_points);


    /// Perform radius search with multiple radii.
    ///
    /// \param query_points Query points. Must be 2D, with shape {n, d}, same
    /// dtype with dataset_points.
    /// \param radii list of radius. Must be 1D, with shape {n, }.
    /// \return Tuple of Tensors: (indices, distances, num_neighbors):
    /// - indicecs: Tensor of shape {total_num_neighbors,}, dtype Int64.
    /// - distances: Tensor of shape {total_num_neighbors,}, same dtype with
    /// dataset_points.
    /// - num_neighbors: Tensor of shape {n,}, dtype Int64.
    std::tuple<Tensor, Tensor, Tensor> SearchRadius(const Tensor &query_points,
                                                    const Tensor &radii);

    /// Perform radius search.
    ///
    /// \param query_points Query points. Must be 2D, with shape {n, d}, same
    /// dtype with dataset_points.
    /// \param radius Radius.
    /// \return Tuple of Tensors, (indices, distances, num_neighbors):
    /// - indicecs: Tensor of shape {total_num_neighbors,}, dtype Int64.
    /// - distances: Tensor of shape {total_num_neighbors,}, same dtype with
    /// dataset_points.
    /// - num_neighbors: Tensor of shape {n}, dtype Int64.
    std::tuple<Tensor, Tensor, Tensor> SearchRadius(const Tensor &query_points,
                                                    double radius);

    /// Get dimension of the dataset points.
    /// \return dimension of dataset points.
    int GetDimension() const;

    /// Get size of the dataset points.
    /// \return number of points in dataset.
    size_t GetDatasetSize() const;

    /// Get dtype of the dataset points.
    /// \return dtype of dataset points.
    Dtype GetDtype() const;

protected:
    Tensor dataset_points_;
    // std::unique_ptr<NanoFlannIndexHolderBase> holder_;
};
}  // namespace nns
}  // namespace core
}  // namespace open3d
