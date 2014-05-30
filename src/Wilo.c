/*
** WiloPLR - Communication with Wilo pumps.
**
** (C) 2009-2014 by Christoph Schueler <github.com/Christoph2,
**                                      cpu12.gems@googlemail.com>
**
**
** All Rights Reserved
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; version 2 of the License.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
**
** s. FLOSS-EXCEPTION.txt
*/

#define WRITE(x)

#define DP_CHECKSUM(dp) ((dp).address + (dp).type + (dp).valueHi + (dp).valueLo)


static void writeDatapoint(Wilo_DatapointType const * const dataPoint);


void Wilo_WriteRequest(uint8 address, uint8 telegramType,
    uint8 numberOfWritePoints, Wilo_DatapointType const * const writePoints,
    uint8 numberOfReadPoints, Wilo_DatapointType const * const readPoints) {

    uint8 idx;
    uint8 checksum = address + telegramType;

    WRITE(address);
    WRITE(telegramType)

    checksum += numberOfWritePoints;
    WRITE(numberOfWritePoints);

    for (idx = (uint8)0; idx < numberOfWritePoints; ++idx) {
        checksum += DP_CHECKSUM(writePoints[idx]);
        writeDatapoint(&writePoints[idx])
    }


    checksum += numberOfReadPoints;
    WRITE(numberOfReadPoints);

    for (idx = (uint8)0; idx < numberOfReadPoints; ++idx) {
        checksum += DP_CHECKSUM(readPoints[idx]);
        writeDatapoint(&readPoints[idx])
    }

    WRITE(checksum);
}


static void writeDatapoint(Wilo_DatapointType const * const dataPoint);
{

    WRITE(dataPoint->address);
    WRITE(dataPoint->type);
    WRITE(dataPoint->valueHi);
    WRITE(dataPoint->valueLo);
}

