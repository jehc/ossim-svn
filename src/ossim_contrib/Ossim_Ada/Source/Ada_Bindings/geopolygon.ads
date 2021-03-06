--*****************************************************************************
-- Copyright (C) 2003 James E. Hopper. 
--
-- This is free software; you can redistribute it and/or
-- modify it under the terms of the GNU General Public License
-- as published by the Free Software Foundation.
--
-- This software is distributed in the hope that it will be useful,
-- but WITHOUT ANY WARRANTY; without even the implied warranty of
-- MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
--
-- You should have received a copy of the GNU General Public License
-- along with this software. If not, write to the Free Software
-- Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-
-- 1307, USA.
--
-- See the GPL in the COPYING.GPL file for more details.
--
-- AUTHOR: James E. Hopper (hopperj@macconnect.com)
--
--*****************************************************************************
with Interfaces.C.Extensions;
use Interfaces.C.Extensions;
with Interfaces; use Interfaces;
with GPt;
with Ossim_Constants; 
 use Ossim_Constants;
package GeoPolygon is

    type Object is tagged private;

    function Create(C_Object : Void_Ptr) return Object;

    function Create return Object;

    procedure Delete(Polygon : Object);

    procedure AddPoint(
        Polygon 	: Object;
        GeoPoint	: GPt.Object);

    procedure SetOrdering(
        Polygon 	: Object;
        Order		: OssimVertexOrdering);

    function C_Object(Polygon : Object) return Void_Ptr;

private

    type Object is tagged
    record
        OssimObject	: Void_Ptr;
    end record;

end GeoPolygon;

