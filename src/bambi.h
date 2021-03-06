/* bambi.h

    Copyright (C) 2016 Genome Research Ltd.

    Author: Jennifer Liddle <js10@sanger.ac.uk>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU Affero General Public License as published
by the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Affero General Public License for more details.

You should have received a copy of the GNU Affero General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __BAMBI_H__
#define __BAMBI_H__

#define INDEX_SEPARATOR "-"
#define QUAL_SEPARATOR " "

#include "config.h"
#include "hts_addendum.h"
#include "array.h"

const char *bambi_version(void);
void parse_tags(va_t *tags, char *arg);

#endif

