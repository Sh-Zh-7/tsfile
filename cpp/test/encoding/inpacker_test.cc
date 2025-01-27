/*
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * License); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License a
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 */
#include <gtest/gtest.h>

#include <bitset>

#include "encoding/intpacker.h"

namespace storage {

TEST(IntPackerTest, Pack8Values) {
    IntPacker int_packer(10);
    int64_t values[NUM_OF_INTS] = {100, 200, 300, 400, 500, 600, 700, 800};
    unsigned char buf[10 * NUM_OF_INTS / 8] = {0};

    int_packer.pack_8values(values, 0, buf);

    // Generated using Java Edition
    unsigned char expected_buf[10 * NUM_OF_INTS / 8] = {25,  12, 132, 177, 144,
                                                        125, 37, 138, 243, 32};
    for (int i = 0; i < 10 * NUM_OF_INTS / 8; i++) {
        EXPECT_EQ(buf[i], expected_buf[i]);
    }
}

TEST(IntPackerTest, Unpack8Values) {
    IntPacker int_packer(10);
    unsigned char buf[4 * NUM_OF_INTS] = {25,  12, 132, 177, 144,
                                          125, 37, 138, 243, 32};
    int64_t values[NUM_OF_INTS] = {0};

    int_packer.unpack_8values(buf, 0, values);

    // Generated using Java Edition
    int expected_values[NUM_OF_INTS] = {100, 200, 300, 400, 500, 600, 700, 800};
    for (int i = 0; i < NUM_OF_INTS; i++) {
        EXPECT_EQ(values[i], expected_values[i]);
    }
}

}  // namespace storage