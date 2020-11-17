
#import <Foundation/Foundation.h>
#import "LabelPrinterObject.h"
#import "LabelPrinterSDK_Defines.h"
#import <UIKit/UIKit.h>

//////////////////////////////////////////////////////////////////////////////////
@class LabelPrinterSDK;
@protocol LabelPrinterSDKDelegate<NSObject>

@required
- (void)willConnect:(LabelPrinterSDK *)controller
            printer:(LabelPrinterObject *)printer;
- (void)didConnect:(LabelPrinterSDK *)controller
           printer:(LabelPrinterObject *)printer;
- (void)didNotConnect:(LabelPrinterSDK *)controller
              printer:(LabelPrinterObject *)printer
            withError:(NSError *)error;
- (void)didDisconnect:(LabelPrinterSDK *)controller
              printer:(LabelPrinterObject *)printer DEPRECATED_ATTRIBUTE;
- (void)didBeBrokenConnection:(LabelPrinterSDK *)controller
                      printer:(LabelPrinterObject *)printer
                    withError:(NSError *)error;

- (void)willLookupPrinter:(LabelPrinterSDK *)controller;

- (void)didFindPrinter:(LabelPrinterSDK *)controller
               printer:(LabelPrinterObject *)printer;

- (void)didLookupPrinters:(LabelPrinterSDK *)controller
              printerList:(NSArray *)printerList;

- (void)canNotFoundPrinter;


@optional
- (void)message:(LabelPrinterSDK *)controller
           text:(NSString *)text DEPRECATED_ATTRIBUTE;
- (void)hasDataAvailable:(LabelPrinterSDK *)controller
                    data:(NSData*)data;
@end
//////////////////////////////////////////////////////////////////////////////////



@interface LabelPrinterSDK : NSObject
{
    
}

@property (weak, nonatomic)                id<LabelPrinterSDKDelegate>    delegate;

/* getting SDK Informations */
+(NSString*)getSDKVersionString;
+(NSString*)getReleasedDateString;


/* search APIs */
-(NSArray*)getPairedDevices;
-(NSArray*)getPairedDevices:(NSError**) errorCode
                     action:(NSInteger) action DEPRECATED_ATTRIBUTE; //  if (action!=_SHOW_BLUETOOTH_SETTINGS_NEVER), the result is nil.

-(NSArray*)getSearchedDevices;
- (void)lookupPrinterWithCount:(CGFloat) lookupCount
                      interval:(CGFloat) interval;

+ (void) setEnableLog:(BOOL)enable saveFile:(BOOL)saveFile hexDump:(BOOL)hexDump;

- (__SDK_RESULT_CODES_) CancelToLookupPrinter;


/* connect APIs */
-(__SDK_RESULT_CODES_) open;
-(__SDK_RESULT_CODES_) close;
-(__SDK_RESULT_CODES_) connectWithTarget:(LabelPrinterObject*)printer timeout:(NSInteger)timeout;
-(__SDK_RESULT_CODES_) connectWithAddress:(NSString*)address port:(NSString*) port;   // WifiPrinter's IPAddress or BluetoothPrinter's Mac(port is nil)
-(__SDK_RESULT_CODES_) connectWithSerialNumber:(NSString*)serialNumber;

-(BOOL) isConnected;
-(__SDK_RESULT_CODES_) disconnect;
-(__SDK_RESULT_CODES_) disconnectWithTimeout:(NSInteger)timeout;

-(NSMutableArray*) getDeviceFontList;
-(NSMutableArray*) getVectorFontList;
-(NSMutableArray*) getDrawBlockOptions;
-(NSMutableArray*) getDrawCircleSizes;
-(NSMutableArray*) getBarcodeType1D;
-(NSMutableArray*) getBarcodeHRI;
-(NSInteger)       getDpi;
-(NSInteger)       getMaxWidth;



/* printing someting APIs */
/**************************************************************************************************
 *  select encoding
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) setCurrentEncoding:(NSStringEncoding)encoding;  //refer to __SDK_ENCODING_OPTIONS

/**************************************************************************************************
 *  checkStatus
 - call example : [_printer checkPrinterStatus:^(NSInteger status){  NSLog(@"myStatus : %d", status);  }];
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) checkPrinterStatus:(blockType1)statusReceiver;

- (NSString *) getModelName;

- (NSString *) getFirmwareVersion;

/**************************************************************************************************
 *  Do Print...
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) doPrint:(NSInteger)numberOfCopies;


/**************************************************************************************************
 *  Print Raw Data...
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) printRawData:(NSData*)rawData;


/**************************************************************************************************
 *  DrawText
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) drawTextDeviceFont:(NSString*)text
                                xPosition:(NSInteger)xPostion
                                yPosition:(NSInteger)yPostion
                            fontSelection:(char)fontSelection
                                fontWidth:(NSInteger)fontWidth
                               fontHeight:(NSInteger)fontHeight
                rightSideCharacterSpacing:(NSInteger)rightSideCharacterSpacing
                             fontRotation:(NSInteger)fontRotation
                                  reverse:(BOOL)reverse
                                     bold:(BOOL)bold
                            textAlignment:(NSInteger)textAlignment;

-(__SDK_RESULT_CODES_) drawTextVectorFont:(NSString*)text
                                xPosition:(NSInteger)xPostion
                                yPosition:(NSInteger)yPostion
                            fontSelection:(char)fontSelection
                                fontWidth:(NSInteger)fontWidth
                               fontHeight:(NSInteger)fontHeight
                rightSideCharacterSpacing:(NSInteger)rightSideCharacterSpacing
                             fontRotation:(NSInteger)fontRotation
                                  reverse:(BOOL)reverse
                                     bold:(BOOL)bold
                                   italic:(BOOL)italic
            textWriteDirectionRightToLeft:(BOOL)textWriteDirectionRightToLeft
                            textAlignment:(NSInteger)textAlignment;


/**************************************************************************************************
 *  Draw 1D Barcode
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) drawBarcode1D:(NSString*)data
                           xPosition:(NSInteger)xPostion
                           yPosition:(NSInteger)yPostion
                         barcodeType:(NSInteger)barcodeType
                         widthNarrow:(NSInteger)widthNarrow
                           widthWide:(NSInteger)widthWide
                              height:(NSInteger)height
                                 hri:(NSInteger)hri
                      quietZoneWidth:(NSInteger)quietZoneWidth
                            rotation:(NSInteger)rotation;

/**************************************************************************************************
 *  Draw 2D Barcodes
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) drawBarcodeMexiCode:(NSString*)data
                                 xPosition:(NSInteger)xPostion
                                 yPosition:(NSInteger)yPostion
                                      mode:(NSInteger)mode;


-(__SDK_RESULT_CODES_) drawBarcodePDF417:(NSString*)data
                               xPosition:(NSInteger)xPostion
                               yPosition:(NSInteger)yPostion
                         maximumRowCount:(NSInteger)maximumRowCount       // 3~90
                      maximumColumnCount:(NSInteger)maximumColumnCount    // 1~30
                    errorCorrectionLevel:(NSInteger)errorCorrectionLevel
                   dataCompressionMethod:(NSInteger)dataCompressionMethod
                        printBarcodeText:(BOOL)printBarcodeText
                      barcodeOriginPoint:(NSInteger)barcodeOriginPoint
                             moduleWidth:(NSInteger)moduleWidth   // 2~9
                               barHeight:(NSInteger)barHeight     // 4~99
                                rotation:(NSInteger)rotation;


-(__SDK_RESULT_CODES_) drawBarcodeQRCode:(NSString*)data
                               xPosition:(NSInteger)xPostion
                               yPosition:(NSInteger)yPostion
                             barcodeSize:(NSInteger)barcodeSize   // 1~4
                                   model:(NSInteger)model
                     errorColectionLevel:(NSInteger)errorColectionLevel
                                rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeDataMatrix:(NSString*)data
                                   xPosition:(NSInteger)xPostion
                                   yPosition:(NSInteger)yPostion
                                 barcodeSize:(NSInteger)barcodeSize   // 1~4
                                     reverse:(BOOL)reverse
                                    rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeAztec:(NSString*)data
                              xPosition:(NSInteger)xPostion
                              yPosition:(NSInteger)yPostion
                            barcodeSize:(NSInteger)barcodeSize    // 1~10
                        extendedChannel:(BOOL)extendedChannel
                   errorCorrectionLevel:(NSInteger)errorCorrectionLevel
                             menuSymbol:(BOOL)menuSymbol
                        numberOfSymbols:(NSInteger)numberOfSymbols
                             optionalID:(NSString*)optionalID
                               rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_)drawBarcodeCode49:(NSString*)data
                              xPosition:(NSInteger)xPostion
                              yPosition:(NSInteger)yPostion
                            widthNarrow:(NSInteger)widthNarrow
                              widthWide:(NSInteger)widthWide
                                 height:(NSInteger)height
                                    hri:(NSInteger)hri
                           startingMode:(NSInteger)startingMode
                               rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeCodaBlock:(NSString*)data
                                  xPosition:(NSInteger)xPostion
                                  yPosition:(NSInteger)yPostion
                                widthNarrow:(NSInteger)widthNarrow
                                  widthWide:(NSInteger)widthWide
                                     height:(NSInteger)height
                              securityLevel:(BOOL)securityLevel
                   numberOfCharactersPerrow:(NSInteger)numberOfCharactersPerrow    //  2~62
                                       mode:(char)mode
                        numberOfRowToEncode:(NSInteger)numberOfRowToEncode;  //  'modeA' : 1~18  else 2~4

-(__SDK_RESULT_CODES_) drawBarcodeMicroPDF:(NSString*)data
                                 xPosition:(NSInteger)xPostion
                                 yPosition:(NSInteger)yPostion
                               moduleWidth:(NSInteger)moduleWidth     // 2~8
                             barcodeHeight:(NSInteger)barcodeHeight   // 1~99
                                      mode:(NSInteger)mode            // 0~33
                                  rotation:(NSInteger)rotation;


/**************************************************************************************************
 *  Draw Special Barcode
 *************************************************************************************************/
-(__SDK_RESULT_CODES_) drawBarcodeIMB:(NSString*)data
                            xPosition:(NSInteger)xPostion
                            yPosition:(NSInteger)yPostion
                     printBarcodeText:(BOOL)printBarcodeText
                             rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeMSI:(NSString*)data
                            xPosition:(NSInteger)xPostion
                            yPosition:(NSInteger)yPostion
                          widthNarrow:(NSInteger)widthNarrow
                            widthWide:(NSInteger)widthWide
                               height:(NSInteger)height
                  checkDigitSelection:(NSInteger)checkDigitSelection
                 printCheckDigitInHRI:(BOOL)printCheckDigitInHRI
                                  hri:(NSInteger)hri
                             rotation:(NSInteger)rotation;


-(__SDK_RESULT_CODES_) drawBarcodePlessey:(NSString*)data
                                xPosition:(NSInteger)xPostion
                                yPosition:(NSInteger)yPostion
                              widthNarrow:(NSInteger)widthNarrow
                                widthWide:(NSInteger)widthWide
                                   height:(NSInteger)height
                          printCheckDigit:(BOOL)printCheckDigit
                                      hri:(NSInteger)hri
                                 rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeTLC39:(NSString*)data
                              xPosition:(NSInteger)xPostion
                              yPosition:(NSInteger)yPostion
                            widthNarrow:(NSInteger)widthNarrow
                              widthWide:(NSInteger)widthWide
                                 height:(NSInteger)height
                 rowHeightOfMicroPDF417:(NSInteger)rowHeightOfMicroPDF417
               narrowWidthOfMicroPDF417:(NSInteger)narrowWidthOfMicroPDF417
                               rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeRSS:(NSString*)data
                            xPosition:(NSInteger)xPostion
                            yPosition:(NSInteger)yPostion
                          barcodeType:(NSInteger)barcodeType
                        magnification:(NSInteger)magnification   // 1~10
                      separatorHeight:(NSInteger)separatorHeight // 1~2
                        barcodeHeight:(NSInteger)barcodeHeight   //  This parameter only affects the UCC/EAN barcode type and CC-A/B/C barcode Type.
                         segmentWidth:(NSInteger)segmentWidth    // 0~22
                             rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBarcodeGS1DataBar:(NSString*)data
                                   xPosition:(NSInteger)xPostion
                                   yPosition:(NSInteger)yPostion
                                 barcodeType:(NSInteger)barcodeType
                               magnification:(NSInteger)magnification   // 1~10
                             separatorHeight:(NSInteger)separatorHeight // 1~2
                               barcodeHeight:(NSInteger)barcodeHeight   //  This parameter only affects the UCC/EAN barcode type and CC-A/B/C barcode Type.
                                segmentWidth:(NSInteger)segmentWidth    // 0~22
                                    rotation:(NSInteger)rotation;

-(__SDK_RESULT_CODES_) drawBlock:(NSInteger)startPosX
                       startPosY:(NSInteger)startPosY
                         endPosX:(NSInteger)endPosX
                         endPosY:(NSInteger)endPosY
                          option:(char)option
                       thickness:(NSInteger)thickness;


-(__SDK_RESULT_CODES_) drawCircle:(NSInteger)startPosX
                        startPosY:(NSInteger)startPosY
                    sizeSelection:(NSInteger)sizeSelection
                       multiplier:(NSInteger)multiplier;

-(__SDK_RESULT_CODES_) drawImage:(UIImage*)image
                       stratPosX:(NSInteger)startPosX
                       startPosY:(NSInteger)startPosY
                           width:(NSInteger)width;

-(__SDK_RESULT_CODES_) drawImage:(UIImage *)image
                       stratPosX:(NSInteger)startPosX
                       startPosY:(NSInteger)startPosY
                           width:(NSInteger)width
                    useDithering:(BOOL)useDithering;

-(__SDK_RESULT_CODES_) drawImage:(UIImage *)image
                       stratPosX:(NSInteger)startPosX
                       startPosY:(NSInteger)startPosY
                           width:(NSInteger)width
                           level:(NSUInteger)level
                    useDithering:(BOOL)useDithering;

-(__SDK_RESULT_CODES_) drawImage:(UIImage *)image
                       stratPosX:(NSInteger)startPosX
                       startPosY:(NSInteger)startPosY
                           width:(NSInteger)width
                           level:(NSUInteger)level
                    useDithering:(BOOL)useDithering
                    compressType:(__SDK_COMPRESS_TYPE)compressType;

-(__SDK_RESULT_CODES_) drawPDF:(NSString *)filepath
                     stratPosX:(NSInteger)startPosX
                     startPosY:(NSInteger)startPosY
                         width:(NSInteger)width
                         level:(NSUInteger)level
                  useDithering:(BOOL)useDithering
                          page:(NSInteger)page;

-(__SDK_RESULT_CODES_) printPDF:(NSString*)filepath
                      startPosX:(NSInteger)startPosX
                      startPosY:(NSInteger)startPosY
                      startPage:(NSInteger)startPage
                        endPage:(NSInteger)endPage
                          width:(NSInteger)width
                          level:(NSUInteger)level
                   useDithering:(BOOL)useDithering;


-(__SDK_RESULT_CODES_) setOrientation:(NSInteger)orientation;

#pragma mark - about setting
///
-(__SDK_RESULT_CODES_) setICS:(NSInteger)ics codepage:(NSInteger)cp;

// __SDK_SPEED_VALUE reference in LabelPrinterSDK_Defines.h
-(__SDK_RESULT_CODES_) setSpeed:(NSInteger) speedValue;

-(__SDK_RESULT_CODES_) setDensity:(NSInteger) densityValue;  //  0~20

// __SDK_PRINTING_TYPE reference in LabelPrinterSDK_Defines.h
// Thermal Direct , Thermal Transfer
-(__SDK_RESULT_CODES_) setPrintingType:(char)printingType;

// __SDK_MEDIA_TYPE reference in LabelPrinterSDK_Defines.h
-(__SDK_RESULT_CODES_) setLength:(NSInteger) labelLength
                       gepLength:(NSInteger) gapLength
                       mediaType:(char) mediaType
                    offsetLength:(NSInteger)offsetLength;

-(__SDK_RESULT_CODES_) setMargin:(NSInteger)horizontalMargin
                  verticalMargin:(NSInteger)verticalMargin;

-(__SDK_RESULT_CODES_) setOffset:(NSInteger)offsetValue; //  -100 ~ 100

-(__SDK_RESULT_CODES_) setCuttingPosition:(NSInteger)cuttiongPosition;  //  -100 ~ 100

-(__SDK_RESULT_CODES_) setAutoCutter:(BOOL)     enableAutoCutter
                       cuttingPeriod:(NSInteger)cuttingPeriod;

-(__SDK_RESULT_CODES_) setWidth:(NSInteger) widthValue;

-(__SDK_RESULT_CODES_) setRewinder:(BOOL)enableRewinder;


#pragma mark - about RFID ( for rfid printer )

/**
 @brief setupRFID
 @param rfidType value area is 0~5 (
    0 = none,
    1 = ISO_18000_6_Type_A,
    2 = ISO_18000_6_Type_B,
    3 = Class_0,
    4 = Class_1,
    5 = Class_1_Gen 2 ( default )
 )
 @param numberOfRetries value area is 1~10 (default 3)
 @param numberOfLabel value area is 1~5 (default 2)
 @param radioPower value area is 0~30 (default 15)
*/
-(__SDK_RESULT_CODES_) setupRFIDWithRfidType:(NSInteger) rfidType
                             numberOfRetries:(NSInteger) numberOfRetries
                               numberOfLabel:(NSInteger) numberOfLabel
                                  radioPower:(NSInteger) radioPower
NS_SWIFT_NAME(setupRFID(rfidType:numberOfRetries:numberOfLabel:radioPower:));


-(__SDK_RESULT_CODES_) calibrateRFID;

-(__SDK_RESULT_CODES_) setRFIDPositionWithPosition:(NSInteger) position
NS_SWIFT_NAME(setRFIDPosition(position:));

/**
 @brief writeRFID
 @param dataType value area is 0~3 (
    0 = ASCII,
    1 = Hex,
    2 = EPC,
    3 = User Hex
 )
 @param startingBlockNumber value area is 4~10 (default 4)
 @param dataLength value area is 2~12 (default 12)
 @param data write data
 @warning If the startingBlockNumber+dataLength exceeds 16, an _SDK_RESULT_FAIL_INVALID_PARAMETER error is returned.
*/
-(__SDK_RESULT_CODES_) writeRFIDWithDataType:(NSInteger) dataType
                         startingBlockNumber:(NSInteger) startingBlockNumber
                                  dataLength:(NSInteger) dataLength
                                        data:(NSString*) data
NS_SWIFT_NAME(writeRFID(dataType:startingBlockNumber:dataLength:data:));

/**
 @brief setRFIDPassword
 @warning If the parameter length is not 8, an _SDK_RESULT_FAIL_INVALID_PARAMETER error is returned.
*/
-(__SDK_RESULT_CODES_) setRFIDPasswordWithOldAccessPwd:(NSString*) oldAccessPwd
                                            oldKillPwd:(NSString*) oldKillPwd
                                          newAccessPwd:(NSString*) newAccessPwd
                                            newKillPwd:(NSString*) newKillPwd
NS_SWIFT_NAME(setRFIDPassword(oldAccessPwd:oldKillPwd:newAccessPwd:newKillPwd:));

-(__SDK_RESULT_CODES_) lockRFID;


/**
 @brief setEPCDataStructure
 @param totalSize total epc data size
 @param fieldSizes Size for each field, only number
 @code [totalSize:10, fieldSizes:"2,3,5"]
 @endcode
 @warning If the sum of fieldSizes is different from totalsize, an _SDK_RESULT_FAIL_INVALID_PARAMETER error is returned.
*/

-(__SDK_RESULT_CODES_) setEPCDataStructureWithTotalSize:(NSInteger) totalSize
                                             fieldSizes:(NSString*) fieldSizes
NS_SWIFT_NAME(setEPCDataStructure(totalSize:fieldSizes:));

@end


