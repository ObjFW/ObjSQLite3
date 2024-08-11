/*
 * Copyright (c) 2020, 2021, 2023, 2024 Jonathan Schleifer <js@nil.im>
 *
 * https://fl.nil.im/objsqlite3
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#import <ObjFW/ObjFW.h>

#import "SL3Connection.h"

@interface Tests: OFObject <OFApplicationDelegate>
@end

OF_APPLICATION_DELEGATE(Tests)

@implementation Tests
- (void)applicationDidFinishLaunching: (OFNotification *)notification
{
	OFIRI *IRI = [OFIRI fileIRIWithPath: @"tests.db"];
	OFFileManager *fileManager = [OFFileManager defaultManager];
	SL3Connection *conn;
	SL3PreparedStatement *stmt;

	if ([fileManager fileExistsAtIRI: IRI])
		[fileManager removeItemAtIRI: IRI];

	conn = [SL3Connection connectionWithIRI: IRI];

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

	stmt = [conn prepareStatement: @"SELECT * FROM test"];
	for (size_t i = 0; [stmt step]; i++) {
		OFNumber *a;
		OFString *b;
		OFData *c;

		OFEnsure([stmt columnCount] == 3);
		OFEnsure([[stmt nameForColumn: 0] isEqual: @"a"]);
		OFEnsure([[stmt nameForColumn: 1] isEqual: @"b"]);
		OFEnsure([[stmt nameForColumn: 2] isEqual: @"c"]);

		switch (i) {
		case 0:
			a = [OFNumber numberWithInt: 5];
			b = @"String";
			c = [OFData dataWithItems: "abc"
					    count: 3];
			break;
		case 1:
			a = [OFNumber numberWithInt: 7];
			b = @"Test";
			c = [OFData dataWithItems: "xyz"
					    count: 3];
			break;
		default:
			OFEnsure(0);
		}

		OFEnsure([[stmt objectForCurrentRowAtColumn: 0] isEqual: a]);
		OFEnsure([[stmt objectForCurrentRowAtColumn: 1] isEqual: b]);
		OFEnsure([[stmt objectForCurrentRowAtColumn: 2] isEqual: c]);

		OFEnsure([[stmt currentRowArray] isEqual:
		    ([OFArray arrayWithObjects: a, b, c, nil])]);
		OFEnsure([[stmt currentRowDictionary] isEqual:
		    ([OFDictionary dictionaryWithKeysAndObjects:
		    @"a", a, @"b", b, @"c", c, nil])]);
	}

	[OFApplication terminate];
}
@end
