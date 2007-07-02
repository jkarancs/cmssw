#ifndef RecoLocalTracker_SiPixelClusterizer_SiPixelClusterProducer_h
#define RecoLocalTracker_SiPixelClusterizer_SiPixelClusterProducer_h

//---------------------------------------------------------------------------
//! \class SiPixelClusterProducer
//!
//! \brief EDProducer to cluster PixelDigis into SiPixelClusters.
//!
//! SiPixelClusterProducer is an EDProducer subclass (i.e., a module)
//! which orchestrates clustering of PixelDigis to SiPixelClusters.
//! Consequently, the input is edm::DetSetVector<PixelDigi> and the output is
//! edm::DetSetVector<SiPixelCluster>.
//!
//! SiPixelClusterProducer invokes one of descendents from PixelClusterizerBase,
//! e.g. PixelThresholdClusterizer (which is the only available option 
//! right now).  SiPixelClusterProducer loads the PixelDigis,
//! and then iterates over DetIds, invoking PixelClusterizer's clusterizeDetUnit
//! to perform the clustering.  clusterizeDetUnit() returns a DetSetVector of
//! SiPixelClusters, which are then recorded in the event.
//!
//! The calibrations are not loaded at the moment (v1), although that is
//! being planned for the near future.
//!
//! \author porting from ORCA by Petar Maksimovic (JHU). 
//!         DetSetVector implementation by Vincenzo Chiochia (Uni Zurich)        
//!
//! \version v1, Oct 26, 2005  
//!
//---------------------------------------------------------------------------

#include "RecoLocalTracker/SiPixelClusterizer/interface/PixelClusterizerBase.h"

//#include "Geometry/CommonDetUnit/interface/TrackingGeometry.h"

#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"


#include "DataFormats/Common/interface/DetSetVector.h"
#include "DataFormats/SiPixelDigi/interface/PixelDigi.h"
#include "DataFormats/SiPixelCluster/interface/SiPixelCluster.h"
#include "DataFormats/Common/interface/EDProduct.h"


#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/Handle.h"
#include "FWCore/Framework/interface/ESHandle.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/ParameterSet/interface/InputTag.h"


namespace cms
{
  class SiPixelClusterProducer : public edm::EDProducer
  {
  public:
    //--- Constructor, virtual destructor (just in case)
    explicit SiPixelClusterProducer(const edm::ParameterSet& conf);
    virtual ~SiPixelClusterProducer();

    //--- Factory method to make PixelClusterizers depending on the ParameterSet
    //--- Not sure if we need to make more than one clusterizer to run concurrently
    //--- on different parts of the detector (e.g., one for the barrel and the 
    //--- one for the forward).
    void setupClusterizer();

    //--- The top-level event method.
    virtual void produce(edm::Event& e, const edm::EventSetup& c);

    //--- Execute the algorithm(s).
    void run(const edm::DetSetVector<PixelDigi> & input,
	     edm::ESHandle<TrackerGeometry>     & geom);

  private:
    edm::ParameterSet conf_;
    // TO DO: maybe allow a map of pointers?
    std::string clusterMode_;               // user's choice of the clusterizer
    PixelClusterizerBase * clusterizer_;    // what we got (for now, one ptr to base class)
    bool readyToCluster_;                   // needed clusterizers valid => good to go!
    edm::InputTag src_;
    std::vector<edm::DetSet<SiPixelCluster> > theClusterVector; // cache to hold all clusters
  };
}


#endif
