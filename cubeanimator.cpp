/*********************************************************************
 *  Author  : Himangshu Saikia
 *  Init    : Thursday, October 12, 2017 - 11:11:30
 *
 *  Project : KTH Inviwo Modules
 *
 *  License : Follows the Inviwo BSD license model
 *********************************************************************
 */

#include <labtransformations/cubeanimator.h>
#include <cmath>

namespace inviwo
{

// The Class Identifier has to be globally unique. Use a reverse DNS naming scheme
const ProcessorInfo CubeAnimator::processorInfo_
{
    "org.inviwo.CubeAnimator",      // Class identifier
    "Cube Animator",                // Display name
    "KTH Labs",                 // Category
    CodeState::Experimental,  // Code state
    Tags::None,               // Tags
};

const ProcessorInfo CubeAnimator::getProcessorInfo() const
{
    return processorInfo_;
}


CubeAnimator::CubeAnimator()
    :Processor()
    // Ports
    , meshIn_("meshIn")
    , meshOut_("meshOut")
    // Properties 
    // For a FloatProperty 
    // variablename(identifier, display name, init value, minvalue, maxvalue)
    , radius_("radius", "Radius", 1, 1, 8)
    , innerradius_("innerradius", "Inner_Radius", 1, 1, 3)
    , rotation_("rotation", "Rotation", 1, 1, 2)
{
    // Add ports
    addPort(meshIn_);
    addPort(meshOut_);
    
    // Add properties
    addProperty(radius_);
    addProperty(innerradius_);
    addProperty(rotation_);

}


void CubeAnimator::process()
{
    // Clone the input mesh
    if (!meshIn_.getData()) return;
    auto mesh = meshIn_.getData()->clone();

    // Get the matrix that defines where the mesh is currently
    auto matrix = mesh->getWorldMatrix();
    
    // Transform the mesh (TODO)
    auto newmatrix = mesh->getWorldMatrix();
    
    float outercircle1 = 4*cos(radius_.get());
    float outercircle2 = 4*sin(radius_.get());
    float innercircle1 = -cos(innerradius_.get());
    float innercircle2 = -sin(innerradius_.get());

    matrix *= glm::translate(vec3(outercircle1+innercircle1, outercircle2+innercircle2, 0));
    matrix *= glm::rotate(newmatrix, rotation_.get(), vec3(0, 0, 1));



    // Update
    mesh->setWorldMatrix(matrix);
	
    // Set output
    meshOut_.setData(mesh);
}

} // namespace

