#ifndef __L1Trigger_L1THGCal_HGCalClusteringImpl_h__
#define __L1Trigger_L1THGCal_HGCalClusteringImpl_h__

#include <array> 
#include <string>
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "L1Trigger/L1THGCal/interface/HGCalTriggerGeometryBase.h"
#include "DataFormats/L1THGCal/interface/HGCalTriggerCell.h"
#include "DataFormats/ForwardDetId/interface/HGCalDetId.h"
#include "DataFormats/L1THGCal/interface/HGCalCluster.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

class HGCalClusteringImpl{

public:
  
    HGCalClusteringImpl( const edm::ParameterSet & conf);    


    /* dR-algorithms */
    bool isPertinent( const l1t::HGCalTriggerCell & tc, 
                      const l1t::HGCalCluster & clu, 
                      double distXY) const;

    void clusterizeDR( const edm::PtrVector<l1t::HGCalTriggerCell> & triggerCellsPtrs,
                     l1t::HGCalClusterBxCollection & clusters 
        );

    /* NN-algorithms */    
    void mergeClusters( l1t::HGCalCluster & main_cluster, 
                        const l1t::HGCalCluster & secondary_cluster ) const;
    
    void NNKernel( const std::vector<edm::Ptr<l1t::HGCalTriggerCell>> &reshuffledTriggerCells,
                   l1t::HGCalClusterBxCollection & clusters,
                   const HGCalTriggerGeometryBase & triggerGeometry
        );
        
    void clusterizeNN( const edm::PtrVector<l1t::HGCalTriggerCell> & triggerCellsPtrs,
                     l1t::HGCalClusterBxCollection & clusters,
                     const HGCalTriggerGeometryBase & triggerGeometry 
        );


private:
    
    double seedThreshold_;
    double triggerCellThreshold_;
    double dr_;
    std::string clusteringAlgorithmType_;
    /* Number of Endcaps = 2, Maximum number of layer in EE + FH = 28 + 12 = 40 */
    void triggerCellReshuffling( const edm::PtrVector<l1t::HGCalTriggerCell> & triggerCellsPtrs, 
                                 std::array<std::array<std::vector<edm::Ptr<l1t::HGCalTriggerCell>>,40>,2> & reshuffledTriggerCells );


};

#endif
