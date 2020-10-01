/*
 * Copyright (c) 2020, Jonathan Schleifer <js@nil.im>
 *
 * https://fossil.nil.im/objsqlite3
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice is present in all copies.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


#import <ObjFW/ObjFW.h>

#import "SL3Connection.h"

@interface Tests: OFObject <OFApplicationDelegate>
@end

OF_APPLICATION_DELEGATE(Tests)

@implementation Tests
- (void)applicationDidFinishLaunching
{
	OFFileManager *fileManager = [OFFileManager defaultManager];
	SL3Connection *conn;
	SL3PreparedStatement *stmt;

	if ([fileManager fileExistsAtPath: @"tests.db"])
	    [fileManager removeItemAtPath: @"tests.db"];

	conn = [SL3Connection connectionWithPath: @"tests.db"];

	[conn executeStatement: @"CREATE TABLE test (a INT, b TEXT, c BLOB)"];

	stmt = [conn prepareStatement:
	    @"INSERT INTO test (a, b, c) VALUES ($a, $b, $c)"];
	[stmt bindWithArray: [OFArray arrayWithObjects:
	    [OFNumber numberWithInt: 5],
	    @"String",
	    [OFData dataWithItems: "abc"
			    count: 3],
	    nil]];
	[stmt step];

	stmt = [conn prepareStatement:
	    @"INSERT INTO test (a, b, c) VALUES ($a, $b, $c)"];
	[stmt bindWithDictionary: [OFDictionary dictionaryWithKeysAndObjects:
	    @"$a", [OFNumber numberWithInt: 7],
	    @"$b", @"Test",
	    @"$c", [OFData dataWithItems: "xyz"
				   count: 3],
	    nil]];
	[stmt step];

	[OFApplication terminate];
}
@end
