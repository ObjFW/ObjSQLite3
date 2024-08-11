/*
 * Copyright (c) 2020 Jonathan Schleifer <js@nil.im>
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

#include <sqlite3.h>

OF_ASSUME_NONNULL_BEGIN

@class SL3Connection;

@interface SL3PreparedStatement: OFObject
{
#ifdef SL3_PUBLIC_IVARS
@public
#endif
	SL3Connection *_connection;
	sqlite3_stmt *_stmt;
}

@property (readonly, nonatomic) OFArray *rowArray;
@property (readonly, nonatomic)
    OFDictionary OF_GENERIC(OFString *, id) *rowDictionary;

- (void)bindWithArray: (OFArray *)array;
- (void)bindWithDictionary:
    (OFDictionary OF_GENERIC(OFString *, id) *)dictionary;
- (void)clearBindings;
- (bool)step;
- (id)objectForColumn: (size_t)column;
- (size_t)columnCount;
- (OFString *)nameForColumn: (size_t)column;
- (void)reset;
@end

OF_ASSUME_NONNULL_END
