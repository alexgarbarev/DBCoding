//
//  DBCoder.h
//  qliq
//
//  Created by Aleksey Garbarev on 06.12.12.
//
//
#import "FMDatabase.h"

@class DBCodingService;
@protocol DBScheme;

typedef void(^DBStatement)(NSString *query, NSArray *args);
typedef id(^DBInsertingBlock)(id object, id<DBScheme> scheme, NSString *column);
typedef void(^DBInsertingForeignBlock)(id object, id<DBScheme> scheme, NSString *foreignKey);


@interface DBCoder(DBService)

- (id)primaryKeyToEncode;

- (id<DBScheme>)scheme;

- (DBCoder *)decoderForColumn:(NSString *)column withScheme:(id<DBScheme>)scheme;

/* one-to-one relations */
- (void) enumerateOneToOneRelatedObjects:(DBInsertingBlock)block;

/* many-to-many relations */
- (NSArray *)allManyToManyConnections;
- (void)enumerateManyToManyCodersForConnection:(DBTableConnection *)connection usingBlock:(void(^)(DBCoder *connectionCoder))block;
- (void)enumerateManyToManyRelationCoders:(void(^)(DBCoder *connection_coder, DBTableConnection *connection))block;

/* one-to-many relations */
- (NSArray *)allOneToManyForeignKeys;
- (void)enumerateOneToManyRelatedObjectsForKey:(NSString *)foreignKey withBlock:(void(^)(id object, id<DBScheme>scheme))block;
- (void)enumerateOneToManyRelatedObjects:(DBInsertingForeignBlock)block;

/* Init for decoding */
- (id)initWithResultSet:(FMResultSet *)resultSet scheme:(id<DBScheme>)scheme dbService:(DBCodingService *)service;

/* Init for encoding object */
- (id)initWithObject:(id)object scheme:(id<DBScheme>)scheme;

/* Init for many-to-many relations */
- (id)initWithConnection:(DBTableConnection *)connection;

/* Access to statements */
- (void) updateStatement:(DBStatement) statement;
- (void) deleteStatement:(DBStatement) statement;
- (void) insertStatement:(DBStatement) statement replace:(BOOL) replace;

@end