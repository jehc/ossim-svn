#include <ossim/base/ossimVisitor.h>
#include <ossim/base/ossimConnectableObject.h>


ossimVisitor::ossimVisitor(int visitorType)
:m_visitorType(static_cast<VisitorType>(visitorType)),
m_stopTraversalFlag(false)
{
   
}

ossimVisitor::ossimVisitor(const ossimVisitor& src)
:m_visitorType(src.m_visitorType),
m_markNode(src.m_markNode),
m_stopTraversalFlag(src.m_stopTraversalFlag)
{
}

ossimVisitor::VisitorType ossimVisitor::getVisitorType()const
{
   return m_visitorType;
}

void  ossimVisitor::setVisitorType(int vType)
{
   m_visitorType = (VisitorType)(vType&VISIT_ALL);
}

void ossimVisitor::turnOffVisitorType(int vType)
{
   m_visitorType = (VisitorType)(((~vType) & m_visitorType)&VISIT_ALL);
}

void ossimVisitor::reset()
{
   m_markNode.clear();
}

void ossimVisitor::visit(ossimObject* obj)
{
   m_markNode.insert(obj);
}

void ossimVisitor::visit(ossimConnectableObject* obj)
{
   ossimVisitor::visit(static_cast<ossimObject*>(obj));
}

bool ossimVisitor::hasVisited(ossimObject* obj)const
{
   return m_markNode.find(obj) != m_markNode.end(); 
}

bool ossimVisitor::stopTraversal()const
{
   return m_stopTraversalFlag;
}

ossimIdVisitor::ossimIdVisitor(const ossimId& id, int visitorType)
:ossimVisitor(visitorType),
m_id(id)
{
}

ossimIdVisitor::ossimIdVisitor(const ossimIdVisitor& src)
:ossimVisitor(src),
m_connectableObject(src.m_connectableObject),
m_id(src.m_id)
{
}

ossimRefPtr<ossimVisitor> ossimIdVisitor::dup()const
{
   return new ossimIdVisitor(*this);
}

void ossimIdVisitor::visit(ossimConnectableObject* obj)
{
   ossimVisitor::visit(obj);
   if(obj->getId() == m_id)
   {
      m_connectableObject = obj;
      m_stopTraversalFlag = true;
   }
}

void ossimIdVisitor::reset()
{
   m_connectableObject = 0;
}

ossimConnectableObject* ossimIdVisitor::getObject()
{
   return m_connectableObject;
}

const ossimConnectableObject* ossimIdVisitor::getObject()const
{
   return m_connectableObject;
}

void ossimIdVisitor::setId(const ossimId& id)
{
   m_id = id;
}

const ossimId& ossimIdVisitor::getId()const
{
   return m_id;
}

ossimCollectionVisitor::ossimCollectionVisitor(int visitorType)
:ossimVisitor(visitorType)
{
}

ossimCollectionVisitor::ossimCollectionVisitor(const ossimCollectionVisitor& src)
:m_collection(src.m_collection)
{
}

ossimCollectionVisitor::ListRef& ossimCollectionVisitor::getObjects()
{
   return m_collection;
}

const ossimCollectionVisitor::ListRef& ossimCollectionVisitor::getObjects()const
{
   return m_collection;
}

void ossimCollectionVisitor::reset()
{
   ossimVisitor::reset();
   m_collection.clear();
}

ossimConnectableObject* ossimCollectionVisitor::getObject(ossim_uint32 idx)
{
   if(idx < m_collection.size())
   {
      return m_collection[idx].get();
   }
   
   return 0;
}

const ossimConnectableObject* ossimCollectionVisitor::getObject(ossim_uint32 idx)const
{
   if(idx < m_collection.size())
   {
      return m_collection[idx].get();
   }
   
   return 0;
}


ossimTypeNameVisitor::ossimTypeNameVisitor(int visitorType)
:ossimCollectionVisitor(visitorType)
{
}

ossimTypeNameVisitor::ossimTypeNameVisitor(const ossimString& typeName, bool firstOfTypeFlag, int visitorType)
:ossimCollectionVisitor(visitorType),
m_typeName(typeName),
 m_firstOfTypeFlag(firstOfTypeFlag)
{
}

ossimTypeNameVisitor::ossimTypeNameVisitor(const ossimTypeNameVisitor& src)
:m_typeName(src.m_typeName),
 m_firstOfTypeFlag(src.m_firstOfTypeFlag)
{
}

ossimRefPtr<ossimVisitor> ossimTypeNameVisitor::dup()const
{
   return new ossimTypeNameVisitor(*this);
}

void ossimTypeNameVisitor::visit(ossimConnectableObject* obj)
{
   if(!hasVisited(obj))
   {
      ossimCollectionVisitor::visit(obj);
      if(obj&&obj->canCastTo(m_typeName))
      {
         m_collection.push_back(obj);
         if(m_firstOfTypeFlag) m_stopTraversalFlag = true;
      }
  }
}

void ossimTypeNameVisitor::setTypeName(const ossimString& typeName)
{
   m_typeName = typeName;
}

const ossimString& ossimTypeNameVisitor::getTypeName()const
{
   return m_typeName;
}

ossimTypeIdVisitor::ossimTypeIdVisitor(int visitorType)
:ossimCollectionVisitor(visitorType)
{
}

ossimTypeIdVisitor::ossimTypeIdVisitor(const RTTItypeid& typeId, bool firstOfTypeFlag, int visitorType)
:ossimCollectionVisitor(visitorType),
m_typeId(typeId),
m_firstOfTypeFlag(firstOfTypeFlag)
{
}

ossimTypeIdVisitor::ossimTypeIdVisitor(const ossimTypeIdVisitor& src)
:m_typeId(src.m_typeId),
m_firstOfTypeFlag(src.m_firstOfTypeFlag)
{
}

ossimRefPtr<ossimVisitor> ossimTypeIdVisitor::dup()const
{
   return new ossimTypeIdVisitor(*this);
}

void ossimTypeIdVisitor::setTypeId(const RTTItypeid& typeId)
{
   m_typeId = typeId;
}

const RTTItypeid& ossimTypeIdVisitor::getTypeId()const
{
   return m_typeId;
}

void ossimTypeIdVisitor::visit(ossimConnectableObject* obj)
{
   if(!hasVisited(obj))
   {
      ossimCollectionVisitor::visit(obj);
      if(obj&&obj->canCastTo(m_typeId))
      {
         m_collection.push_back(obj);
         if(m_firstOfTypeFlag) m_stopTraversalFlag = true;
      }
   }
}

ossimEventVisitor::ossimEventVisitor(ossimEvent* evt, int visitorType)
:ossimVisitor(visitorType),
m_event(evt)
{
}
ossimEventVisitor::ossimEventVisitor(const ossimEventVisitor& src)
:ossimVisitor(src),
m_event(src.m_event)
{
}

ossimRefPtr<ossimVisitor> ossimEventVisitor::dup()const
{
   return new ossimEventVisitor(*this);
}

void ossimEventVisitor::visit(ossimConnectableObject* obj)
{
   if(!hasVisited(obj))
   {
      obj->fireEvent(*m_event);
   }
   ossimVisitor::visit(obj);
}

