/**
 * @file   icarusalg/Utilities/CanvasUtils.h
 * @brief  Helper functions based on _art_/canvas.
 * @author Gianluca Petrillo (petrillo@slac.stanford.edu)
 * @date   January 13, 2022
 * 
 * This library is header only.
 */

#ifndef ICARUSALG_UTILITIES_CANVASUTILS_H
#define ICARUSALG_UTILITIES_CANVASUTILS_H

// framework libraries
#include "canvas/Persistency/Common/Ptr.h"
#include "canvas/Persistency/Provenance/BranchDescription.h"
#include "canvas/Persistency/Provenance/ProductID.h"
#include "canvas/Utilities/Exception.h"

// C++ standard libraries
#include <type_traits> // std::enable_if_t


namespace util {
  
  //----------------------------------------------------------------------------
  /**
   * @brief Reads and returns the input tag of the producer of `productID`.
   * @tparam Event type of event to read data from (`art::Event` interface)
   * @param event event to read data products from
   * @param productID reference data product
   * @return the input tag of the producer of `productID`
   * @throw art::Exception (error code: `art::errors::ProductNotFound`) if no
   *        input tag could be found
   * 
   * This utility facilitates the traversal of associations.
   * Assuming that a pointer to a data product element is available, we may need
   * to read another data product from the same producer (e.g. from a pointer to
   * a `recob::Track` from a collection, we want to learn the associations of
   * that track to `recob::Hit`, assuming that the same module that produced the
   * tracks also produced their associations to hit).
   * This is trivial if the input tag of the data product element is known, but
   * it's not if that data product is instead known only by a
   * pointer/association.
   * In that case, this function discovers the needed input tag. Example:
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~{.cpp}
   * auto const& assns
   *   = event.getProduct<std::vector<recob::Hit>>(inputTagOf(trackPtr.id()));
   * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
   * where `trackPtr` is a `art::Ptr<recob::Track>` that may come for example
   * from a `recob::PFParticle`/`recob::Track` association.
   */
  template <typename Event>
  art::InputTag inputTagOf(Event const& event, art::ProductID const& productID);
  
  
  /**
   * @brief Reads and returns the input tag of the product with the specified
   *        `handle`.
   * @tparam Event type of event to read data from (`art::Event` interface)
   * @tparam Handle type of handle
   * @param event event to read data products from
   * @param handle data product handle
   * @return the input tag of the producer of data product at `handle`
   * @throw art::Exception (error code: `art::errors::ProductNotFound`) if no
   *        input tag could be found
   * @see `inputTag(Event const&, art::ProductID const&)`
   * 
   * This utility is a wrapper of the version working on product ID.
   */
  template <typename Event, typename Handle>
  std::enable_if_t<
    std::is_void_v<std::void_t<typename Handle::HandleTag>>,
    art::InputTag
    >
  inputTagOf(Event const& event, Handle const& handle)
    { return inputTagOf(event, handle.id()); }
  
  
  /**
   * @brief Reads and returns the input tag of the product `ptr` points to.
   * @tparam Event type of event to read data from (`art::Event` interface)
   * @tparam T type of the datum pointed by the pointer
   * @param event event to read data products from
   * @param ptr _art_ pointer to the data product element
   * @return the input tag of the producer of data product of `ptr`
   * @throw art::Exception (error code: `art::errors::ProductNotFound`) if no
   *        input tag could be found
   * @see `inputTag(Event const&, art::ProductID const&)`
   * 
   * This utility is a wrapper of the version working on product ID.
   */
  template <typename Event, typename T>
  art::InputTag inputTagOf(Event const& event, art::Ptr<T> const& ptr)
    { return inputTagOf(event, ptr.id()); }
  
  
  //----------------------------------------------------------------------------


} // namespace util


//------------------------------------------------------------------------------
//---  template implementation
//------------------------------------------------------------------------------
template <typename Event>
art::InputTag util::inputTagOf
  (Event const& event, art::ProductID const& productID)
{
  
  cet::exempt_ptr<art::BranchDescription const> metaDescr
    = event.getProductDescription(productID);
  if (metaDescr) return metaDescr->inputTag();
  
  throw art::Exception(art::errors::ProductNotFound)
    << "Branch (and input tag) not found for product ID " << productID;
  
} // util::inputTagOf()


//------------------------------------------------------------------------------


#endif // ICARUSALG_UTILITIES_CANVASUTILS_H
