//-----------------------------------------------------------------------------
// File:  Init.h
//
// License:  See top level LICENSE.txt file.
//
// Author:  David Burken
//
// Description: Class declaration for Init.  Handles ossim initialization.
//
//-----------------------------------------------------------------------------
// $Id: Init.h 19748 2011-06-12 15:34:56Z dburken $

#ifndef ossimjniInit_HEADER
#define ossimjniInit_HEADER 1


#include <ossimjni/Constants.h>

namespace ossimjni
{
   class OSSIMJNIDLL Init
   {
   public:

      /** @brief destructor */
      ~Init();

      /**
       * @brief Instance method.
       *
       * @return The instance of this class.
       */
      static ossimjni::Init* instance();

      /** @brief Initialize method. */
      void initialize();
      
      /**
       * @brief Initialize method.
       *
       * @param argc Argument count.
       *
       * @param argv Array of args.
       */
      void initialize(int argc, char* argv[]);

   private:
      
      /** @brief default constructor - hidden from use */
      Init();

      /** @brief copy constructor - hidden from use */
      Init(const ossimjni::Init& obj);

      /** @brief assignment operator - hidden from use */ 
      const ossimjni::Init& operator=(const ossimjni::Init& obj);

      /** @brief The single static instance of this class. */
      static ossimjni::Init* m_instance;

      /** Flag to ignore duplicate initialization calls. */
      bool m_initCalledFlag;
   };

} // End of namespace ossimjni.

#endif /* #ifndef ossimjniInit_HEADER */
