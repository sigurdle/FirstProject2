#if 0
				for (int nTexture = 0; nTexture < nTextures; nTexture++)
				{
					const uint8* textureData = textureBitmap[nTexture].Scan0;
					int textureWidth = textureBitmap[nTexture].Width;
					int textureHeight = textureBitmap[nTexture].Height;
					int32 textureRowBytes = textureBitmap[nTexture].Stride;

					int tex_s = pTexture[nTexture]->x_table[(((color[5 + nTexture*2+0]<<8) / color[4])) & 511];
					int tex_t = pTexture[nTexture]->y_table[(((color[5 + nTexture*2+1]<<8) / color[4])) & 511];
				}
	#if 0
						int tex_s = (int)(color[4] / color[6]) % textureWidth;
						if (tex_s < 0) tex_s += textureWidth;

						int tex_t = (int)(color[5] / color[6]) % textureHeight;
						if (tex_t < 0) tex_t += textureHeight;
	#endif

					{
					//	nTexture = 0;
					//	uint32 mask = m_enable.m_texEnabledFlag;
					//	while (mask)
						{
							//if (nTexture == 1)// && mask & 1)
					//		if (mask & 1)
							for (int nTexture = 0; nTexture < nTextures; nTexture++)
							{
								const uint8* textureData = textureBitmap[nTexture].Scan0;
								int textureWidth = textureBitmap[nTexture].Width;
								int textureHeight = textureBitmap[nTexture].Height;
								int32 textureRowBytes = textureBitmap[nTexture].Stride;

							//	int* x_table = pTexture->x_table;
							//	int* y_table = pTexture->y_table;

								int tex_s = pTexture[nTexture]->x_table[(((color[5 + nTexture*2+0]<<8) / color[4])) & 511];
								int tex_t = pTexture[nTexture]->y_table[(((color[5 + nTexture*2+1]<<8) / color[4])) & 511];

							//	int tex_s = pTexture[nTexture]->x_table[((((LONGLONG)color[5 + nTexture*2+0]<<8) * color[4]) >> 16) & 511];
							//	int tex_t = pTexture[nTexture]->y_table[((((LONGLONG)color[5 + nTexture*2+1]<<8) * color[4]) >> 16) & 511];

								switch (textureBitmap[nTexture].PixelFormat)
								{
								case RGB_24:
									{
										PixelRGB_24* tp = (PixelRGB_24*)(textureData + textureRowBytes*tex_t + tex_s*3);
										
										dwcolor_unit[nTexture][0] = tp->r;
										dwcolor_unit[nTexture][1] = tp->g;
										dwcolor_unit[nTexture][2] = tp->b;
										dwcolor_unit[nTexture][3] = 255;
									}
									break;

								case GRAY_8:
									{
										uint8* tp = (uint8*)(textureData + textureRowBytes*tex_t + tex_s);

										dwcolor_unit[nTexture][0] = *tp;
										dwcolor_unit[nTexture][1] = *tp;
										dwcolor_unit[nTexture][2] = *tp;
										dwcolor_unit[nTexture][3] = 255;
									}
									break;
								}
							}

						//	nTexture++;
						//	mask >>= 1;
						//	if (nTexture == nTextures) break;
						}

						// Input start is fragment color
						__asm
						{
							MOVAPD	xmm2,xmm0
							PSRAD		xmm2,triShift
						}
						/*
						dwcolor_final[0] = color[0]>>triShift;
						dwcolor_final[1] = color[1]>>triShift;
						dwcolor_final[2] = color[2]>>triShift;
						dwcolor_final[3] = color[3]>>triShift;
						*/

					//	nTexture = 0;
					//	mask = m_enable.m_texEnabledFlag;
					//	while (mask)
						{
							//if (nTexture == 1)//
					//		if (mask & 1)
							for (int nTexture = 0; nTexture < nTextures; nTexture++)
							{
								switch (pTexture[nTexture]->m_envMode)
								{
								case GL_REPLACE:
									{
										const uint32* pdwcolor_unit = &dwcolor_unit[nTexture][0];

										dwcolor_final[0] = pdwcolor_unit[0];
										dwcolor_final[1] = pdwcolor_unit[1];
										dwcolor_final[2] = pdwcolor_unit[2];
										dwcolor_final[3] = pdwcolor_unit[3];

										/*
										pdwcolor_unit[0] = dwcolor_unit[nTexture][0];
										pdwcolor_unit[1] = dwcolor_unit[nTexture][1];
										pdwcolor_unit[2] = dwcolor_unit[nTexture][2];
										pdwcolor_unit[3] = dwcolor_unit[nTexture][3];

										__asm
										{
											MOVAPD xmm2,[pdwcolor_unit]
											CVTDQ2PS	xmm0,xmm2	// dword -> float
											MULPS	xmm0,xmm7	// / 255
										}
										*/
									}
									break;

								case GL_MODULATE:
									{
									//	const uint32* pdwcolor_unit = &dwcolor_unit[nTexture][0];

										dwcolor_texture[0] = dwcolor_unit[nTexture][0];
										dwcolor_texture[1] = dwcolor_unit[nTexture][1];
										dwcolor_texture[2] = dwcolor_unit[nTexture][2];
										dwcolor_texture[3] = dwcolor_unit[nTexture][3];

									//	dwcolor_final
									//	dwcolor_final[0] = pdwcolor_unit[0];
									//	dwcolor_final[1] = pdwcolor_unit[1];
									//	dwcolor_final[2] = pdwcolor_unit[2];
									//	dwcolor_final[3] = pdwcolor_unit[3];

										/*
										dwcolor_final[0] = (dwcolor_final[0] * pdwcolor_unit[0]) >> 8;
										dwcolor_final[1] = (dwcolor_final[1] * pdwcolor_unit[1]) >> 8;
										dwcolor_final[2] = (dwcolor_final[2] * pdwcolor_unit[2]) >> 8;
										dwcolor_final[3] = (dwcolor_final[3] * pdwcolor_unit[3]) >> 8;
										*/
										__asm
										{
											MOVAPD	xmm3,[dwcolor_texture]
											PMULHD	xmm2,xmm3
											PSRAD		xmm2,8
										}

										/*
										__asm
										{
											MOVAPD xmm2,[pdwcolor_unit]
										//	CVTDQ2PS	xmm3,xmm2	// dword -> float
										//	MULPS xmm3,xmm7	// / 255

											MULPS	xmm0,xmm3
										}
										*/
									}
									break;

								case GL_COMBINE:
									{
										/*
										pdwcolor_unit[0] = dwcolor_unit[nTexture][0];
										pdwcolor_unit[1] = dwcolor_unit[nTexture][1];
										pdwcolor_unit[2] = dwcolor_unit[nTexture][2];
										pdwcolor_unit[3] = dwcolor_unit[nTexture][3];

										__asm
										{
											MOVAPD xmm2,[pdwcolor_unit]
											CVTDQ2PS	xmm3,xmm2	// dword -> float
											MULPS	xmm3,xmm7	// / 255

											MULPS	xmm0,xmm3

										}

										break;
										*/

	#if 0
										switch (pTexture[nTexture]->m_combineRGB)
										{
										case GL_DOT3_RGB:
											{
												float arg0[4];
												float arg1[4];

												pdwcolor_unit[0] = dwcolor_unit[nTexture][0];
												pdwcolor_unit[1] = dwcolor_unit[nTexture][1];
												pdwcolor_unit[2] = dwcolor_unit[nTexture][2];
												pdwcolor_unit[3] = dwcolor_unit[nTexture][3];

												__asm
												{
													MOVAPD xmm2,[pdwcolor_unit]
													CVTDQ2PS	xmm3,xmm2	// dword -> float
													MULPS xmm3,xmm7	// / 255

													MOVUPD [arg0],xmm0
													MOVUPD [arg1],xmm3
												}

												/*
												arg1[0] /= 255;
												arg1[1] /= 255;
												arg1[2] /= 255;
												*/

												float scalar = 4 *	((arg0[0] - 0.5) * (arg1[0] - 0.5) +
																			(arg0[1] - 0.5) * (arg1[1] - 0.5) +
																			(arg0[2] - 0.5) * (arg1[2] - 0.5));
												if (scalar < 0) scalar = 0;
												else if (scalar > 1) scalar = 1;

												arg0[0] = scalar;
												arg0[1] = scalar;
												arg0[2] = scalar;

												__asm
												{
													MOVUPD xmm0,[arg0]
												}
											}
											break;

										default:
											ASSERT(0);
										}
	#endif
									}
									break;

								case GL_ADD:
									{
									//	dest->r = MIN(255, tp->r + color[0]);
									//	dest->g = MIN(255, tp->g + color[1]);
									//	dest->b = MIN(255, tp->b + color[2]);
									}
									break;

								default:
									ASSERT(0);
								}

								/*
								// Input of next is result of this
								__asm
								{
									MOVAPD xmm0,xmm3
								}
								*/

							//	color[5 + nTexture*2+0] += dcolor[5 + nTexture*2+0];
							//	color[5 + nTexture*2+1] += dcolor[5 + nTexture*2+1];
							}

						//	nTexture++;
						//	mask >>= 1;
						//	if (nTexture == nTextures) break;
						//	break;
						}

						/*
						__asm
						{
							MULPS xmm0,xmm6		// * 255
						//	CVTPS2DQ xmm1,xmm0	// float -> dword
							MOVAPD [dwcolor_final],xmm1
						}
						*/
						__asm
						{
							MOVAPD [dwcolor_final],xmm2
						}

						dest->r = dwcolor_final[0];
						dest->g = dwcolor_final[1];
						dest->b = dwcolor_final[2];
					}

					z += dz;

					if (true)
					{
						__asm
						{
							PADDD	xmm0,xmm1
						}
					}
					else
					{
						color[0] += dcolor[0];
						color[1] += dcolor[1];
						color[2] += dcolor[2];
						color[3] += dcolor[3];
					}

					color[4] += dcolor[4];
					for (int i = 5; i < varying; i++)
					{
						color[i] += dcolor[i];
					}
				//	color[5] += dcolor[5];
				//	color[6] += dcolor[6];

					dest++;
					depth++;
#endif
