#include "usernode.h"

UserNode::UserNode(UserAccess* userData) : data(userData), next(nullptr)
{
}

UserNode::~UserNode()
{
  delete data;
}
