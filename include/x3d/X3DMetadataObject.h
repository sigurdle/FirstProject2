namespace System
{
namespace x3d
{

interface X3DMetadataObject
{
	virtual String getName() = 0;
	virtual String getReference() = 0;

	virtual SFString* getNameField() = 0;
	virtual SFString* getReferenceField() = 0;
};

}	// x3d
}	// System
